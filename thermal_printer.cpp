#include "thermal_printer.h"
//#include "json.data.manager.h"
//#include "display.imageaddr.h"
//#include "system.manager.h"
#include <math.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdarg.h>

#include <unistd.h>
#include <stdlib.h>

#include <QDebug>

#include "ConfigManager.h"
#include "DateFormatManager.h"

#define TRUE    1
#define FALSE   0
//#define NULL    nullptr

bool g_bOnlyComlaser = TRUE;
int g_nInQuiry = 0;
int g_nrecvCount = 0;
char g_recvBuff[WIFI_PRINTER_MAX_BUFFER];


ST_WIFI_PRIINTER g_wifi_printer;
//char g_print_img_body_buff_file_management[1712 * 984];  // Only Y among YUV 420 image body buffer for thermal printer from uncompressed jpg file
//char g_print_img_body_buff_file_logo[1712 * 984];  // David, Add for LOGO file -> (1712x280)

bool g_bExitWifiThread = FALSE;
static int				s_pid_wifi_printer = 0;
static pthread_t		s_tid_wifi_printer = 0;

static int parse_filename(char *filename);
static void *t_wifi_read_packet(void *arg);

unsigned char getPixel(int x, int y, char * img, int swidth)
{
    return (unsigned char)img[y*swidth + x];
}

unsigned char getPixel(int x, int y, unsigned char * img, int swidth)
{
    return (unsigned char)img[y*swidth + x];
}

unsigned char pixelLerp(unsigned char c0, unsigned char c1, float weight)
{
    unsigned char cRet;
    cRet = (unsigned char)floor(c0*weight + c1*(1 - weight) + 0.5);

    return cRet;
}

unsigned char getPixelLerp(float x, float y, char * img, int stride)
{

    int x0, x1, y0, y1;
    float wL, wT;
    unsigned char cT, cB, c00, c10, c01, c11, c;

    x0 = (int)floor(x); x1 = (int)ceil(x);
    y0 = (int)floor(y); y1 = (int)ceil(y);
    wL = (float)(1.0 - (x - x0));
    wT = (float)(1.0 - (y - y0));

    c00 = getPixel(x0, y0, img, stride);
    c10 = getPixel(x1, y0, img, stride);
    c01 = getPixel(x0, y1, img, stride);
    c11 = getPixel(x1, y1, img, stride);

    cT = pixelLerp(c00, c10, wL);
    cB = pixelLerp(c01, c11, wL);
    c = pixelLerp(cT, cB, wT);

    return c;

}

/* ======== resizeImage ========
Parameters
sx : x start of scale
sy : y start of scale
imagewidth : image width size user wants
imageheight : image height size user wants
VRAM : image buffer pointer of scaled image
orgwidth : original image width
orgheight : original image height
orgstride : original image stride
pSrc : original image buffer
*/

void resizeImage(int sx, int sy, int imgwidth, int imgheight, char *pDest, int orgwidth, int orgheight, int orgstride, char *pSrc)
{
    //fprintf(stdout, "=== Resize Function Start ===\n");
    float scaleX, scaleY;
    char * data;
    scaleX = (float)orgwidth / (float)imgwidth;
    scaleY = (float)orgheight / (float)imgheight;

    data = pSrc;
    int i, j = 0;
    for (j = 0; j < imgheight; j++)
    {
        for (i = 0; i < imgwidth; i++)
        {

            unsigned char cInterpol, cScale;
            float x, y;
            unsigned int nIndex = j * imgwidth + i;

            x = (float)(scaleX*i);
            y = (float)(scaleY*j);

            cInterpol = getPixelLerp(x, y, data, orgstride);
            pDest[nIndex] = (char)cInterpol;
        }
    }
}

unsigned char Add_Saturation(unsigned char val1, signed char val2)
{
    int val1_int = (int)val1;
    int val2_int = (int)val2;
    int tmp = val1_int + val2_int;

    if (tmp > 255)
    {
        return 255;
    }
    else if (tmp < 0)
    {
        return 0;
    }
    else
    {
        return (unsigned char)tmp;
    }
}

void Floyd_Steinberg_Dithering(int nWidth, int nHeight, unsigned char* pImg)
{
    //fprintf(stdout, "=== Floyd_Steinberg_Dithering Function Start ===\n");

    int i, j;
    int nQuant_Err;
    int a, b, c, d;
    unsigned char cValPix, cClosestPix;
    for (j = 0; j < nHeight; j++)
    {
        for (i = 0; i < nWidth; i++)
        {
            cValPix = getPixel(i, j, pImg, nWidth);
            if (cValPix < 128)
            {
                nQuant_Err = cValPix;
                pImg[(j - 0) * nWidth + (i - 0)] = 0;
            }
            else
            {
                nQuant_Err = cValPix - 255;
                pImg[(j - 0) * nWidth + (i - 0)] = 255;
            }
            a = (nQuant_Err * 7) / 16;
            b = (nQuant_Err * 3) / 16;
            c = (nQuant_Err * 5) / 16;
            d = (nQuant_Err * 1) / 16;

            if ((i != (nWidth - 1)) && (i != 0) && (j != (nHeight - 1)))
            {
                pImg[(j + 0) * nWidth + (i + 1)] = Add_Saturation((unsigned char)(pImg[(j + 0) * nWidth + (i + 1)]), a);
                pImg[(j + 1) * nWidth + (i - 1)] = Add_Saturation((unsigned char)(pImg[(j + 1) * nWidth + (i - 1)]), b);
                pImg[(j + 1) * nWidth + (i + 0)] = Add_Saturation((unsigned char)(pImg[(j + 1) * nWidth + (i + 0)]), c);
                pImg[(j + 1) * nWidth + (i + 1)] = Add_Saturation((unsigned char)(pImg[(j + 1) * nWidth + (i + 1)]), d);
            }
        }
    }
}

void Atkison_Dithering(int nWidth, int nHeight, unsigned char* pImg)
{
    //fprintf(stdout, "=== Atkison_Dithering Function Start ===\n");
    int i, j;
    int nQuant_Err;
    signed char a;
    unsigned char cValPix;
    for (j = 0; j < nHeight; j++)
    {
        for (i = 0; i < nWidth; i++)
        {
            cValPix = getPixel(i, j, pImg, nWidth);
            if (cValPix < 128)
            {
                nQuant_Err = cValPix;
                pImg[(j - 0) * nWidth + (i - 0)] = 0;
            }
            else
            {
                nQuant_Err = cValPix - 255;
                pImg[(j - 0) * nWidth + (i - 0)] = 255;
            }
            a = (nQuant_Err * 1) / 8;

            if ((i < (nWidth - 2)) && (i != 0) && (j < (nHeight - 2)))
            {
                pImg[(j + 0) * nWidth + (i + 1)] = Add_Saturation((unsigned char)(pImg[(j + 0) * nWidth + (i + 1)]), a);
                pImg[(j + 0) * nWidth + (i + 2)] = Add_Saturation((unsigned char)(pImg[(j + 0) * nWidth + (i + 2)]), a);
                pImg[(j + 1) * nWidth + (i - 1)] = Add_Saturation((unsigned char)(pImg[(j + 1) * nWidth + (i - 1)]), a);
                pImg[(j + 1) * nWidth + (i + 0)] = Add_Saturation((unsigned char)(pImg[(j + 1) * nWidth + (i + 0)]), a);

                pImg[(j + 1) * nWidth + (i + 1)] = Add_Saturation((unsigned char)(pImg[(j + 1) * nWidth + (i + 1)]), a);
                pImg[(j + 2) * nWidth + (i + 0)] = Add_Saturation((unsigned char)(pImg[(j + 2) * nWidth + (i + 0)]), a);
            }
        }
    }
}

void print_wifi_header(int socket)
{
    //WiFi_Printf(socket, "          Bangladesh Police\n");
    //fprintf(stdout, "%s, %s(), %d [DaW-PRT] Print Size = %d Inch \n", __FILE__, __FUNCTION__, __LINE__, g_wifi_printer.size);
    switch (g_wifi_printer.size)
    {
    case 2:	// 2 Inch
    {
        WiFi_Printf(socket, " POLICE OVER-SPEEDING CHALLAN\r\n\r\n");
    }
    break;
    case 3:	// 3 Inch
    {
        WiFi_Printf(socket, "      POLICE OVER-SPEEDING CHALLAN\r\n\r\n");
    }
    break;
    case 4:
    {
        WiFi_Printf(socket, "            POLICE OVER-SPEEDING CHALLAN\r\n\r\n");
    }
    break;
    }
}

void print_wifi_header_office_txt_info(int socket)
{
    //WiFi_Printf(socket, "          Bangladesh Police\n");
    //fprintf(stdout, "%s, %s(), %d [DaW-PRT] TXT - Print Size = %d Inch \n", __FILE__, __FUNCTION__, __LINE__, g_wifi_printer.size);
    switch (g_wifi_printer.size)
    {
    case 2:	// 2 Inch
    {
        WiFi_Printf(socket, " POLICE OVER-SPEEDING CHALLAN\r\n\r\n");
    }
    break;
    case 3:	// 3 Inch
    {
        WiFi_Printf(socket, "      POLICE OVER-SPEEDING CHALLAN\r\n\r\n");
    }
    break;
    case 4:
    {
        WiFi_Printf(socket, "            POLICE OVER-SPEEDING CHALLAN\r\n\r\n");
    }
    break;
    }
}

// David, Add for LOGO file
void print_wifi_image_logo(int socket, int nManufacturer)
{
    char cStandmode[2] = { 0x1b, 0x53 };				// To change standard mode
    int nWrotten = send(socket, cStandmode, 2, 0);

    char cCRLF[2] = { '\r', '\n' };						// to print a blank row
    nWrotten = send(socket, cCRLF, 2, 0);

    // print image
    int nInch = g_wifi_printer.size;
    int nOrgWidth = 192 * nInch;						// Pixel Width for Scale
    // David,
    int nOrgHeight = (int)(nOrgWidth / 1712.0 * 280);	// LOGO Pixel Height for Scale

    int bit[8];
    unsigned char nPix;
    int i, j, k, nIndex, nPrintIndex, nValue;
    unsigned char *pScaledBuff = NULL;
    unsigned char *pPrintBuff = NULL;

    if (nManufacturer == PRINTER_WOOSIM_SYS)		// Woosim Sys.
    {
        char cPagemode[2] = { 0x1b, 0x4c };			// for chaging to page mode
        nWrotten = send(socket, cPagemode, 2, 0);

        char cPageArea[10] = { 0 };	// To set printing area
        cPageArea[0] = 0x1b;									// ESC
        cPageArea[1] = 0x57;									// W
        cPageArea[2] = 0x00;									// xL
        cPageArea[3] = 0x00;									// xH
        cPageArea[4] = 0x00;									// yL
        cPageArea[5] = 0x00;									// yH
        cPageArea[6] = (char)((nOrgWidth & 0xff));				// dxL
        cPageArea[7] = (char)((nOrgWidth >> 8) & 0xff);			// dxH
        cPageArea[8] = (char)((nOrgHeight & 0xff));				// dxL
        cPageArea[9] = (char)((nOrgHeight >> 8) & 0xff);			// dxH
        nWrotten = send(socket, cPageArea, 10, 0);

        char cStartingPoint[6] = { 0x1b, 0x4f, 0x00, };			// To set starting position
        nWrotten = send(socket, cStartingPoint, 6, 0);

        int imageRowBytes = (nOrgWidth / 8) + ((nOrgWidth % 8 == 0) ? 0 : 1);
        //fprintf(stdout, "=== Woosim Sys. Print Image (%d, %d) ===\n", imageRowBytes, nOrgHeight);
        pScaledBuff = (unsigned char*)malloc(nOrgWidth * nOrgHeight);
        pPrintBuff = (unsigned char*)malloc(imageRowBytes * nOrgHeight);

        // David,
        // to get image buffer without information header area after scaling
        //resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
        //	1712, 984, 1712, g_print_img_body_buff_file_logo);
        resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
            1712, 280, 1712, g_print_img_body_buff_file_logo);	// David, LOGO Size

        // to dither image processing
        //Floyd_Steinberg_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);
        Atkison_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);

        char cData[WIFI_PRINTER_MAX_BUFFER] = { 0 };
        for (i = 0; i < nOrgHeight; i++)
        {
            for (j = 0; j < nOrgWidth; j = j + 8)
            {
                nIndex = i * nOrgWidth + j;
                for (k = 0; k < 8; k++)
                {
                    nPix = (unsigned char)pScaledBuff[nIndex + k];
                    bit[k] = (int)(nPix > 0 ? 0 : 1); // 0 : white, 1 : black
                }
                nValue = bit[0] * 128 + bit[1] * 64 + bit[2] * 32 + bit[3] * 16 + bit[4] * 8 +
                    bit[5] * 4 + bit[6] * 2 + bit[7];
                nPrintIndex = (i * nOrgWidth / 8) + (j / 8);
                cData[j / 8] = (char)nValue;
            }

            char cPrintHeader[5] = { 0x1b, 0x58, 0x34, 0 };			// Always to send a wifi-printer one row data
            cPrintHeader[3] = imageRowBytes;
            cPrintHeader[4] = 1;									// it is always OK under 10-inch printer
            nWrotten = send(socket, cPrintHeader, 5, 0);
            nWrotten = send(socket, cData, nOrgWidth / 8, 0);

            cStartingPoint[4] = (char)(((i + 1) & 0xff));			// Start_yL
            cStartingPoint[5] = (char)(((i + 1) >> 8) & 0xff);		// Start_yH
            nWrotten = send(socket, cStartingPoint, 6, 0);			// To set starting position
        }
    }
    else if (nManufacturer == PRINTER_EASTROYCE)		// Eastroyce
    {
        int nPrint_xL = nOrgWidth / 8 % 256;			// xL
        int nPrint_xH = nOrgWidth / 8 / 256;			// xH
        int nPrint_yL = nOrgHeight % 256;				// yL
        int nPrint_yH = nOrgHeight / 256;				// yH
        int nPrintWidth = (nPrint_xH << 8) + nPrint_xL;
        int nPrintHeight = (nPrint_yH << 8) + nPrint_yL;
        nWrotten = 0;

        //fprintf(stdout, "=== Eastroyce Print Image LOGO (%d, %d) ===\n", nPrintWidth, nPrintHeight);
        pScaledBuff = (unsigned char*)malloc(nOrgWidth * nOrgHeight);
        pPrintBuff = (unsigned char*)malloc(nPrintWidth * nPrintHeight + 8);

        ////fprintf(stdout, "%s, %s(), %d [DaW-PRT] pScaledBuff = %s \n", __FILE__, __FUNCTION__, __LINE__, pScaledBuff);
        ////fprintf(stdout, "%s, %s(), %d [DaW-PRT] pPrintBuff = %s \n", __FILE__, __FUNCTION__, __LINE__, pPrintBuff);

        pPrintBuff[0] = 0x1D; pPrintBuff[1] = 0x76;
        pPrintBuff[2] = 0x30; pPrintBuff[3] = 0x00;
        pPrintBuff[4] = nPrint_xL; pPrintBuff[5] = nPrint_xH;
        pPrintBuff[6] = nPrint_yL; pPrintBuff[7] = nPrint_yH;

        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[0] 0x%x \n", pPrintBuff[0]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[1] 0x%x \n", pPrintBuff[1]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[2] 0x%x \n", pPrintBuff[2]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[3] 0x%x \n", pPrintBuff[3]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[4] %d \n", pPrintBuff[4]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[5] %d \n", pPrintBuff[5]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[6] %d \n", pPrintBuff[6]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[7] %d \n", pPrintBuff[7]);

        //fprintf(stdout, "\t [DaW-PRT] nOrgWidth, nOrgHeight (%d, %d) === \n", nOrgWidth, nOrgHeight);

        // David,
        // to get image buffer without information header area after scaling
        //resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
        //	1712, 984, 1712, g_print_img_body_buff_file_logo);
        resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
            1712, 280, 1712, g_print_img_body_buff_file_logo);

        // to dither image processing
        //Floyd_Steinberg_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);
        Atkison_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);

        for (i = 0; i < nOrgHeight; i++)
        {
            for (j = 0; j < nOrgWidth; j = j + 8)
            {
                nIndex = i * nOrgWidth + j;
                for (k = 0; k < 8; k++)
                {
                    nPix = (unsigned char)pScaledBuff[nIndex + k];
                    bit[k] = (int)(nPix > 0 ? 0 : 1); // 0 : white, 1 : black
                }
                nValue = bit[0] * 128 + bit[1] * 64 + bit[2] * 32 + bit[3] * 16 + bit[4] * 8 +
                    bit[5] * 4 + bit[6] * 2 + bit[7];

                nPrintIndex = (i * nOrgWidth / 8) + (j / 8) + 8;
                pPrintBuff[nPrintIndex] = (char)nValue;
            }
        }
        nWrotten = send(socket, pPrintBuff, nPrintWidth * nPrintHeight + 8, 0);
    }
    free(pScaledBuff);
    free(pPrintBuff);
    pScaledBuff = NULL;
    pPrintBuff = NULL;

    nWrotten = send(socket, cStandmode, 2, 0);			// To change standard mode
    //nWrotten = send(socket, cCRLF, 2, 0);				// to print a blank row
}
/////

void print_wifi_image(int socket, int nManufacturer)
{
    char cStandmode[2] = { 0x1b, 0x53 };				// To change standard mode
    int nWrotten = send(socket, cStandmode, 2, 0);

    char cCRLF[2] = { '\r', '\n' };						// to print a blank row
    nWrotten = send(socket, cCRLF, 2, 0);

    // print image
    int nInch = g_wifi_printer.size;
    int nOrgWidth = 192 * nInch;						// Pixel Width for Scale
    int nOrgHeight = (int)(nOrgWidth / 1712.0 * 984);		// Pixel Height for Scale

    int bit[8];
    unsigned char nPix;
    int i, j, k, nIndex, nPrintIndex, nValue;
    unsigned char *pScaledBuff = NULL;
    unsigned char *pPrintBuff = NULL;

    if (nManufacturer == PRINTER_WOOSIM_SYS)		// Woosim Sys.
    {
        char cPagemode[2] = { 0x1b, 0x4c };			// for chaging to page mode
        nWrotten = send(socket, cPagemode, 2, 0);

        char cPageArea[10] = { 0 };	// To set printing area
        cPageArea[0] = 0x1b;									// ESC
        cPageArea[1] = 0x57;									// W
        cPageArea[2] = 0x00;									// xL
        cPageArea[3] = 0x00;									// xH
        cPageArea[4] = 0x00;									// yL
        cPageArea[5] = 0x00;									// yH
        cPageArea[6] = (char)((nOrgWidth & 0xff));					// dxL
        cPageArea[7] = (char)((nOrgWidth >> 8) & 0xff);			// dxH
        cPageArea[8] = (char)((nOrgHeight & 0xff));				// dxL
        cPageArea[9] = (char)((nOrgHeight >> 8) & 0xff);			// dxH
        nWrotten = send(socket, cPageArea, 10, 0);

        char cStartingPoint[6] = { 0x1b, 0x4f, 0x00, };			// To set starting position
        nWrotten = send(socket, cStartingPoint, 6, 0);

        int imageRowBytes = (nOrgWidth / 8) + ((nOrgWidth % 8 == 0) ? 0 : 1);
        //fprintf(stdout, "=== Woosim Sys. Print Image (%d, %d) ===\n", imageRowBytes, nOrgHeight);
        pScaledBuff = (unsigned char*)malloc(nOrgWidth * nOrgHeight);
        pPrintBuff = (unsigned char*)malloc(imageRowBytes * nOrgHeight);

        // to get image buffer without information header area after scaling
        resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
            1712, 984, 1712, g_print_img_body_buff_file_management);

        // to dither image processing
        //Floyd_Steinberg_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);
        Atkison_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);

        char cData[WIFI_PRINTER_MAX_BUFFER] = { 0 };
        for (i = 0; i < nOrgHeight; i++)
        {
            for (j = 0; j < nOrgWidth; j = j + 8)
            {
                nIndex = i * nOrgWidth + j;
                for (k = 0; k < 8; k++)
                {
                    nPix = (unsigned char)pScaledBuff[nIndex + k];
                    bit[k] = (int)(nPix > 0 ? 0 : 1); // 0 : white, 1 : black
                }
                nValue = bit[0] * 128 + bit[1] * 64 + bit[2] * 32 + bit[3] * 16 + bit[4] * 8 +
                    bit[5] * 4 + bit[6] * 2 + bit[7];
                nPrintIndex = (i * nOrgWidth / 8) + (j / 8);
                cData[j / 8] = (char)nValue;
            }

            char cPrintHeader[5] = { 0x1b, 0x58, 0x34, 0 };			// Always to send a wifi-printer one row data
            cPrintHeader[3] = imageRowBytes;
            cPrintHeader[4] = 1;									// it is always OK under 10-inch printer
            nWrotten = send(socket, cPrintHeader, 5, 0);
            nWrotten = send(socket, cData, nOrgWidth / 8, 0);

            cStartingPoint[4] = (char)(((i + 1) & 0xff));			// Start_yL
            cStartingPoint[5] = (char)(((i + 1) >> 8) & 0xff);		// Start_yH
            nWrotten = send(socket, cStartingPoint, 6, 0);			// To set starting position
        }
    }
    else if (nManufacturer == PRINTER_EASTROYCE)		// Eastroyce
    {
        int nPrint_xL = nOrgWidth / 8 % 256;			// xL
        int nPrint_xH = nOrgWidth / 8 / 256;			// xH
        int nPrint_yL = nOrgHeight % 256;				// yL
        int nPrint_yH = nOrgHeight / 256;				// yH
        int nPrintWidth = (nPrint_xH << 8) + nPrint_xL;
        int nPrintHeight = (nPrint_yH << 8) + nPrint_yL;
        nWrotten = 0;

        //fprintf(stdout, "=== Eastroyce Print Image (%d, %d) ===\n", nPrintWidth, nPrintHeight);
        pScaledBuff = (unsigned char*)malloc(nOrgWidth * nOrgHeight);
        pPrintBuff = (unsigned char*)malloc(nPrintWidth * nPrintHeight + 8);

        ////fprintf(stdout, "%s, %s(), %d [DaW-PRT] pScaledBuff = %s \n", __FILE__, __FUNCTION__, __LINE__, pScaledBuff);
        ////fprintf(stdout, "%s, %s(), %d [DaW-PRT] pPrintBuff = %s \n", __FILE__, __FUNCTION__, __LINE__, pPrintBuff);

        pPrintBuff[0] = 0x1D; pPrintBuff[1] = 0x76;
        pPrintBuff[2] = 0x30; pPrintBuff[3] = 0x00;
        pPrintBuff[4] = nPrint_xL; pPrintBuff[5] = nPrint_xH;
        pPrintBuff[6] = nPrint_yL; pPrintBuff[7] = nPrint_yH;

        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[0] 0x%x \n", pPrintBuff[0]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[1] 0x%x \n", pPrintBuff[1]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[2] 0x%x \n", pPrintBuff[2]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[3] 0x%x \n", pPrintBuff[3]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[4] %d \n", pPrintBuff[4]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[5] %d \n", pPrintBuff[5]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[6] %d \n", pPrintBuff[6]);
        ////fprintf(stdout, "\t [DaW-PRT] pPrintBuff[7] %d \n", pPrintBuff[7]);

        //fprintf(stdout, "\t [DaW-PRT] nOrgWidth, nOrgHeight (%d, %d) === \n", nOrgWidth, nOrgHeight);

        // to get image buffer without information header area after scaling
        resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
            1712, 984, 1712, g_print_img_body_buff_file_management);

        // to dither image processing
        //Floyd_Steinberg_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);
        Atkison_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);

        for (i = 0; i < nOrgHeight; i++)
        {
            for (j = 0; j < nOrgWidth; j = j + 8)
            {
                nIndex = i * nOrgWidth + j;
                for (k = 0; k < 8; k++)
                {
                    nPix = (unsigned char)pScaledBuff[nIndex + k];
                    bit[k] = (int)(nPix > 0 ? 0 : 1); // 0 : white, 1 : black
                }
                nValue = bit[0] * 128 + bit[1] * 64 + bit[2] * 32 + bit[3] * 16 + bit[4] * 8 +
                    bit[5] * 4 + bit[6] * 2 + bit[7];

                nPrintIndex = (i * nOrgWidth / 8) + (j / 8) + 8;
                pPrintBuff[nPrintIndex] = (char)nValue;
            }
        }
        nWrotten = send(socket, pPrintBuff, nPrintWidth * nPrintHeight + 8, 0);
    }
    free(pScaledBuff);
    free(pPrintBuff);
    pScaledBuff = NULL;
    pPrintBuff = NULL;

    nWrotten = send(socket, cStandmode, 2, 0);			// To change standard mode
    nWrotten = send(socket, cCRLF, 2, 0);				// to print a blank row
}

// TODO David, Add for Image ZOOM file
void print_wifi_image_zoom(int socket, int nManufacturer)
{
    char cStandmode[2] = { 0x1b, 0x53 };				// To change standard mode
    int nWrotten = send(socket, cStandmode, 2, 0);

    char cCRLF[2] = { '\r', '\n' };						// to print a blank row
    nWrotten = send(socket, cCRLF, 2, 0);

    // print image
    int nInch = g_wifi_printer.size;
    int nOrgWidth = (192 * nInch) *2 ;					// Pixel Width for Scale
    int nOrgHeight = (int)(nOrgWidth / 1712.0 * 984);	// Pixel Height for Scale
    //int nOrgWidth = (192 * nInch) *2 ;					// Pixel Width for Scale
    //int nOrgHeight = (int)(nOrgWidth / 1712.0 * 984);	// Pixel Height for Scale

    int bit[8];
    unsigned char nPix;
    int i, j, k, nIndex, nPrintIndex, nValue;
    unsigned char *pScaledBuff = NULL;
    unsigned char *pPrintBuff = NULL;

    if (nManufacturer == PRINTER_WOOSIM_SYS)		// Woosim Sys.
    {
        char cPagemode[2] = { 0x1b, 0x4c };			// for chaging to page mode
        nWrotten = send(socket, cPagemode, 2, 0);

        char cPageArea[10] = { 0 };	// To set printing area
        cPageArea[0] = 0x1b;									// ESC
        cPageArea[1] = 0x57;									// W
        cPageArea[2] = 0x00;									// xL
        cPageArea[3] = 0x00;									// xH
        cPageArea[4] = 0x00;									// yL
        cPageArea[5] = 0x00;									// yH
        cPageArea[6] = (char)((nOrgWidth & 0xff));				// dxL
        cPageArea[7] = (char)((nOrgWidth >> 8) & 0xff);			// dxH
        cPageArea[8] = (char)((nOrgHeight & 0xff));				// dxL
        cPageArea[9] = (char)((nOrgHeight >> 8) & 0xff);			// dxH
        nWrotten = send(socket, cPageArea, 10, 0);

        char cStartingPoint[6] = { 0x1b, 0x4f, 0x00, };			// To set starting position
        nWrotten = send(socket, cStartingPoint, 6, 0);

        int imageRowBytes = (nOrgWidth / 8) + ((nOrgWidth % 8 == 0) ? 0 : 1);
        //fprintf(stdout, "=== Woosim Sys. Print Image (%d, %d) ===\n", imageRowBytes, nOrgHeight);
        pScaledBuff = (unsigned char*)malloc(nOrgWidth * nOrgHeight);
        pPrintBuff = (unsigned char*)malloc(imageRowBytes * nOrgHeight);

        // David,
        // to get image buffer without information header area after scaling
        resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
            1712, 984, 1712, g_print_img_body_buff_file_management);
        //resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
        //	3424, 1968, 3424, g_print_img_body_buff_file_management);

        // to dither image processing
        //Floyd_Steinberg_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);
        Atkison_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);

        char cData[WIFI_PRINTER_MAX_BUFFER] = { 0 };
        for (i = 0; i < nOrgHeight; i++)
        {
            for (j = 0; j < nOrgWidth; j = j + 8)
            {
                nIndex = i * nOrgWidth + j;
                for (k = 0; k < 8; k++)
                {
                    nPix = (unsigned char)pScaledBuff[nIndex + k];
                    bit[k] = (int)(nPix > 0 ? 0 : 1); // 0 : white, 1 : black
                }
                nValue = bit[0] * 128 + bit[1] * 64 + bit[2] * 32 + bit[3] * 16 + bit[4] * 8 +
                    bit[5] * 4 + bit[6] * 2 + bit[7];
                nPrintIndex = (i * nOrgWidth / 8) + (j / 8);
                cData[j / 8] = (char)nValue;
            }

            char cPrintHeader[5] = { 0x1b, 0x58, 0x34, 0 };			// Always to send a wifi-printer one row data
            cPrintHeader[3] = imageRowBytes;
            cPrintHeader[4] = 1;									// it is always OK under 10-inch printer
            nWrotten = send(socket, cPrintHeader, 5, 0);
            nWrotten = send(socket, cData, nOrgWidth / 8, 0);

            cStartingPoint[4] = (char)(((i + 1) & 0xff));			// Start_yL
            cStartingPoint[5] = (char)(((i + 1) >> 8) & 0xff);		// Start_yH
            nWrotten = send(socket, cStartingPoint, 6, 0);			// To set starting position
        }
    }
    else if (nManufacturer == PRINTER_EASTROYCE)		// Eastroyce
    {
        int nPrint_xL = nOrgWidth / 8 % 256;			// xL
        int nPrint_xH = nOrgWidth / 8 / 256;			// xH
        int nPrint_yL = nOrgHeight % 256;				// yL
        int nPrint_yH = nOrgHeight / 256;				// yH
        int nPrintWidth = (nPrint_xH << 8) + nPrint_xL;
        int nPrintHeight = (nPrint_yH << 8) + nPrint_yL;
        nWrotten = 0;

        //fprintf(stdout, "=== Eastroyce Print Image (%d, %d) ===\n", nPrintWidth, nPrintHeight);
        pScaledBuff = (unsigned char*)malloc(nOrgWidth * nOrgHeight);
        pPrintBuff = (unsigned char*)malloc(nPrintWidth * nPrintHeight + 8);

        //fprintf(stdout, "%s, %s(), %d [DaW-PRT] pScaledBuff = %s \n", __FILE__, __FUNCTION__, __LINE__, pScaledBuff);
        //fprintf(stdout, "%s, %s(), %d [DaW-PRT] pPrintBuff = %s \n", __FILE__, __FUNCTION__, __LINE__, pPrintBuff);

        pPrintBuff[0] = 0x1D; pPrintBuff[1] = 0x76;
        pPrintBuff[2] = 0x30; pPrintBuff[3] = 0x00;
        pPrintBuff[4] = nPrint_xL; pPrintBuff[5] = nPrint_xH;
        pPrintBuff[6] = nPrint_yL; pPrintBuff[7] = nPrint_yH;

        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[0] 0x%x \n", pPrintBuff[0]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[1] 0x%x \n", pPrintBuff[1]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[2] 0x%x \n", pPrintBuff[2]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[3] 0x%x \n", pPrintBuff[3]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[4] %d \n", pPrintBuff[4]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[5] %d \n", pPrintBuff[5]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[6] %d \n", pPrintBuff[6]);
        //fprintf(stdout, "\t [DaW-PRT] pPrintBuff[7] %d \n", pPrintBuff[7]);

        //fprintf(stdout, "\t [DaW-PRT] nOrgWidth, nOrgHeight (%d, %d) === \n", nOrgWidth, nOrgHeight);

        // to get image buffer without information header area after scaling
        resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
            1712, 984, 1712, g_print_img_body_buff_file_management);
        //resizeImage(0, 0, nOrgWidth, nOrgHeight, (char*)pScaledBuff,
        //	3424, 1968, 3424, g_print_img_body_buff_file_management);

        // to dither image processing
        //Floyd_Steinberg_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);
        Atkison_Dithering(nOrgWidth, nOrgHeight, pScaledBuff);

        for (i = 0; i < nOrgHeight; i++)
        {
            for (j = 0; j < nOrgWidth; j = j + 8)
            {
                nIndex = i * nOrgWidth + j;
                for (k = 0; k < 8; k++)
                {
                    nPix = (unsigned char)pScaledBuff[nIndex + k];
                    bit[k] = (int)(nPix > 0 ? 0 : 1); // 0 : white, 1 : black
                }
                nValue = bit[0] * 128 + bit[1] * 64 + bit[2] * 32 + bit[3] * 16 + bit[4] * 8 +
                    bit[5] * 4 + bit[6] * 2 + bit[7];

                nPrintIndex = (i * nOrgWidth / 8) + (j / 8) + 8;
                pPrintBuff[nPrintIndex] = (char)nValue;
            }
        }
        nWrotten = send(socket, pPrintBuff, nPrintWidth * nPrintHeight + 8, 0);
    }
    free(pScaledBuff);
    free(pPrintBuff);
    pScaledBuff = NULL;
    pPrintBuff = NULL;

    nWrotten = send(socket, cStandmode, 2, 0);			// To change standard mode
    nWrotten = send(socket, cCRLF, 2, 0);				// to print a blank row
}
/////

void ClearWiFiRecvBuff(PRINTER_INQUIRY nInq)
{
    memset(g_recvBuff, 0, WIFI_PRINTER_MAX_BUFFER);
    g_nrecvCount = 0;
    g_nInQuiry = nInq;
}

void print_wifi_body(int socket)
{
    if (json_data_manager_get_print_option_ticket_num())	// +- David, printOption Ticket No.(field_id number) print
    {
        //WiFi_Printf(socket, "Ticket No. : %s\n", "AI_99999");
        WiFi_Printf(socket, "Ticket No. : %s_%s\n", g_file_elem_for_printer.prefix, g_file_elem_for_printer.file_id);
    }
    else
    {
        WiFi_Printf(socket, "Ticket No. : \n");
    }

    switch (GetDateFormat())
    {
    case YYYYMMDD:
    {
        WiFi_Printf(socket, "Date : %s/%s/%s\n", g_file_elem_for_printer.year, g_file_elem_for_printer.month, g_file_elem_for_printer.day);

    }
        break;
    case MMDDYYYY:
    {
        WiFi_Printf(socket, "Date : %s/%s/%s\n", g_file_elem_for_printer.month, g_file_elem_for_printer.day, g_file_elem_for_printer.year);

    }
        break;
    case DDMMYYYY:
    {
        WiFi_Printf(socket, "Date : %s/%s/%s\n", g_file_elem_for_printer.day, g_file_elem_for_printer.month, g_file_elem_for_printer.year);

    }
        break;
    }

    WiFi_Printf(socket, "Time : %s:%s:%s\n\n", g_file_elem_for_printer.hour, g_file_elem_for_printer.minute, g_file_elem_for_printer.second);

    //fprintf(stdout, "capture speed : %s\n", g_file_elem_for_printer.laser_capture_speed);

    int limit_speed = atoi(g_file_elem_for_printer.display_limit_speed);
    int capture_limit = atoi(g_file_elem_for_printer.capture_limit_speed);
    int capture_speed = atoi(&g_file_elem_for_printer.laser_capture_speed[1]);
    int capture_distance = atoi(g_file_elem_for_printer.laser_capture_distance);
    if (!strncmp(g_file_elem_for_printer.unit, "S", 1))
    {
        WiFi_Printf(socket, "Speed     Limit : %d km/h\r\n", limit_speed);
        WiFi_Printf(socket, "Capture   Limit : %d km/h\r\n", capture_limit);
        WiFi_Printf(socket, "Violation Speed : %d km/h\r\n", capture_speed);
        WiFi_Printf(socket, "Range           : %d m\r\n\r\n", capture_distance);
    }
    else
    {
        WiFi_Printf(socket, "Speed     Limit : %d mile/h\r\n", limit_speed);
        WiFi_Printf(socket, "Capture   Limit : %d mile/h\r\n", capture_limit);
        WiFi_Printf(socket, "Violation Speed : %d mile/h\r\n", capture_speed);
        WiFi_Printf(socket, "Range           : %d feet\r\n\r\n", capture_distance);
    }

    switch (g_wifi_printer.size)
    {
    case 2:		// 2 inch printer
    {
        WiFi_Printf(socket, "Location : %s\r\n", g_file_elem_for_printer.location.c_str());
        WiFi_Printf(socket, "  GPS(%s, %s)\r\n\r\n", g_file_elem_for_printer.latitude, g_file_elem_for_printer.longitude);

        if (json_data_manager_get_print_option_body())	// +- David, printOption print
        {
            WiFi_Printf(socket, "Vehicle No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's Name \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's License No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Officer's ID %s\r\n\r\n", g_file_elem_for_printer.user_name.c_str());
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Driver \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Officer \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "\r\n\r\n");
        }
        WiFi_Printf(socket, "\r\n");
    }
    break;
    case 3:		// 3 inch printer
    {
        WiFi_Printf(socket, "Location : %s(%s, %s)\r\n\r\n", g_file_elem_for_printer.location.c_str(), g_file_elem_for_printer.latitude, g_file_elem_for_printer.longitude);

        if (json_data_manager_get_print_option_body())	// +- David, printOption print
        {
            WiFi_Printf(socket, "Vehicle No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's Name \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's License No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Officer's ID    : %s\r\n\r\n", g_file_elem_for_printer.user_name.c_str());
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Driver \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Officer \r\n\r\n");
            WiFi_Printf(socket, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "\r\n\r\n");
        }
        WiFi_Printf(socket, "\r\n");
    }
    break;
    case 4:		// 4 inch printer
    {
        WiFi_Printf(socket, "Location : %s(%s, %s)\r\n\r\n", g_file_elem_for_printer.location.c_str(), g_file_elem_for_printer.latitude, g_file_elem_for_printer.longitude);

        if (json_data_manager_get_print_option_body())	// +- David, printOption print
        {
            WiFi_Printf(socket, "Vehicle No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's Name \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's License No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Officer's ID %s\r\n\r\n", g_file_elem_for_printer.user_name.c_str());
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Driver \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Officer \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "\r\n\r\n");
        }
        WiFi_Printf(socket, "\r\n");
    }
    break;
    default:
    {
        WiFi_Printf(socket, "Location : %s(%s, %s)\r\n\r\n", g_file_elem_for_printer.location.c_str(), g_file_elem_for_printer.latitude, g_file_elem_for_printer.longitude);

        if (json_data_manager_get_print_option_body())	// +- David, printOption print
        {
            WiFi_Printf(socket, "Vehicle No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's Name \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Driver's License No. \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Officer's ID    : %s\r\n\r\n", g_file_elem_for_printer.user_name.c_str());
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Driver \r\n\r\n");
            WiFi_Printf(socket, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "Signature of Officer \r\n\r\n");
            WiFi_Printf(socket, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\r\n");
            WiFi_Printf(socket, "\r\n\r\n");
        }
        WiFi_Printf(socket, "\r\n");
    }
    break;
    }

}

void print_wifi_printer(/*char *fullfilename*/)
{
//    parse_filename(fullfilename);
    if (!strncmp(g_file_elem_for_printer.prefix, "AI", 2) || !strncmp(g_file_elem_for_printer.prefix, "AV", 2) || !strncmp(g_file_elem_for_printer.prefix, "MC", 2))
    {
        /************
        Before printing, H10 must check if wifi printer is connected or not to avoid below situations or etc.
        1. Printer power is off with rack of battery after wifi connection
        2. Printer server is out of order with unknown reasons
        ************/

        int nManufacturer = json_data_manager_get_wifi_printer();
        if (connect_wifi_printer() == 1)
        {
            if (g_nInQuiry != INQUIRY_NONE)
            {
                //fprintf(stdout, "[DEBUG] ===== Error : WiFi Printer should be changed : Size %d(%d, %d)=====\n", g_wifi_printer.size, atoi(str_wifi_printer), g_wifi_printer.manufacturer);
                ClearWiFiRecvBuff(INQUIRY_NONE);
                close_wifi_printer_socket();
                //disp_filemanagement_main_run(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
            }
            else
            {
                if (g_bOnlyComlaser)
                {
                    //print_wifi_header(g_wifi_printer.socket);
                    //print_wifi_image(g_wifi_printer.socket, atoi(str_wifi_printer));	// 0 : Woosim, 1 : Eastroyce
                    //print_wifi_body(g_wifi_printer.socket);

                    if (json_data_manager_get_print_option_logo())
                    {
                        // David, Add for LOGO Print
                        //fprintf(stdout, "// [DaW-PRT] === LOGO & TITLE Printing ..... \n");
                        print_wifi_image_logo(g_wifi_printer.socket, nManufacturer);	// LOGO + Title (1712x320)
                        print_wifi_image(g_wifi_printer.socket, nManufacturer);	// 0 : Woosim, 1 : Eastroyce
                        //print_wifi_image_zoom(g_wifi_printer.socket, atoi(str_wifi_printer));	// TODO ZOOM print vehicle number
                        print_wifi_body(g_wifi_printer.socket);
                    }
                    else
                    {
                        //fprintf(stdout, "// [DaW-PRT] === Normal Printing .....  \n");
                        print_wifi_header(g_wifi_printer.socket);
                        print_wifi_image(g_wifi_printer.socket, nManufacturer);	// 0 : Woosim, 1 : Eastroyce
                        print_wifi_body(g_wifi_printer.socket);
                    }
                    //disk_manager_write_summary_tracking_log(fullfilename, &g_file_elem_for_printer, 0.0f, 0.0f, TRUE, TRUE, 2); // bImageOnly param is ignored
                    //disp_filemanagement_main_run(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
                }
                else
                {
                    //WiFi_Printf(g_wifi_printer.socket, " This WiFi Printer Is NOT Supproted \r\n\r\n\r\n");
                    //disp_messagebox_run(CATEGORY_MESSAGEBOX_OK, MESSAGEBOX_CONTENT_WIFI_PRINITER_NOT_SUPPORTED);
                    //fprintf(stdout, "[DEBUG] ===== Error : This WiFi Printer Is NOT Supproted  =====\n");
                }
            }
        }
        else
        {
            //fprintf(stdout, "[DEBUG] ===== Error : WiFi Printer Connectivity Check Before Printing =====\n");
            close_wifi_printer_socket();
            //disp_filemanagement_main_run(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
        }
    }
}

void CreateWiFiReadThreadAndInitPrinter(void)
{
    if (g_wifi_printer.serv_addr != NULL)
    {
        free(g_wifi_printer.serv_addr);
    }
    g_wifi_printer.serv_addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    s_pid_wifi_printer = pthread_create(&s_tid_wifi_printer, NULL, t_wifi_read_packet, NULL);
    if (s_pid_wifi_printer == 0)
    {
        //fprintf(stdout, "=========================================\n");
        //fprintf(stdout, "|     1  Create WiFI Read Thread.        \n");
        //fprintf(stdout, "|     2  s_pid_wifi_printer : %d         \n", s_pid_wifi_printer);
        //fprintf(stdout, "|     3  s_tid_wifi_printer : %d         \n", s_tid_wifi_printer);
        //fprintf(stdout, "=========================================\n");
    }
    else
    {
        //fprintf(stdout, "Error. Create WiFi Printer Check Thread~!!\n");
    }
}

int connect_with_timeout(int sock, struct sockaddr_in res, unsigned long timeout_milli)
{
    int err;
    socklen_t len;
    fd_set writefds;
    struct timeval timeout;
    int flags;

    FD_ZERO(&writefds);
    flags = fcntl(sock, F_GETFL);
    flags = (flags | O_NONBLOCK);
    if (fcntl(sock, F_SETFL, flags) != 0)
    {
        //fprintf(stdout, "Error : fcntl() error\n");
        return -1;
    }
    if (connect(sock, (struct sockaddr*)&res, sizeof(res)) != 0)
    {
        if (errno != EINPROGRESS)
        {
            fprintf(stdout, "Error : connect() error\n");
            return -1;
        }
    }
    timeout.tv_sec = timeout_milli / 1000;
    timeout.tv_usec = (timeout_milli % 1000) * 1000;
    FD_SET(sock, &writefds);
    if (select(sock + 1, NULL, &writefds, NULL, &timeout) <= 0)
    {
        //fprintf(stdout, "Error : connection timeout\n");
        return -1;
    }

    len = sizeof(err);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, (char *)&err, &len);
    if (err)
    {
        //fprintf(stdout, "Error : fcntl() error\n");
        return -1;
    }

    flags = fcntl(sock, F_GETFL);
    flags = (flags & ~O_NONBLOCK);
    if (fcntl(sock, F_SETFL, flags) != 0)
    {
        //fprintf(stdout, "Error : fcntl() error\n");
        return -1;
    }

    return 0;
}

void close_wifi_printer_socket()
{
    shutdown(g_wifi_printer.socket, SHUT_RDWR);
    close(g_wifi_printer.socket);
    //fprintf(stdout, "[DEBUG] ===== Socket Closed(fd : %d) =====\n", g_wifi_printer.socket);

    //g_bExitWifiThread = TRUE;
    //if (s_tid_wifi_printer != 0)
    //{
    //	//fprintf(stdout, "[DEBUG] ===== The Beginning of WiFi Thread Join %d =====\n", s_tid_wifi_printer);
    //	TH_JOIN(s_tid_wifi_printer, NULL);
    //}

    g_wifi_printer.isConnected = FALSE;
    g_wifi_printer.socket = -1;
}



void SetPrinterModelAndSize()
{

    int nManufacturer = json_data_manager_get_wifi_printer();
    ////fprintf(stdout, "[DEBUG] ===== WiFi Printer Manufacturer : %d =====\n", nManufacturer);
    switch (nManufacturer)
    {
    case PRINTER_WOOSIM_SYS:		// Woosim
    {
        if (g_recvBuff[0] == 0x69)
        {
            if (g_nrecvCount > 10)
            {
                char cWoosim_3inch[10] = { 0x33, 0x35, 0x30, 0x28, 0x52, 0x58, 0x29, 0x5f, 0x0d, 0x0a };
                char cWoosim_4inch[10] = { 0x34, 0x35, 0x30, 0x28, 0x52, 0x58, 0x29, 0x5f, 0x0d, 0x0a };

                if (memcmp(&g_recvBuff[1], cWoosim_3inch, sizeof(cWoosim_3inch)) == 0)
                {
                    g_wifi_printer.size = 3;
                    //fprintf(stdout, "[DEBUG] ===== Woosim WiFi Printer 3 inch =====\n");
                    g_nInQuiry = INQUIRY_NONE;
                }
                else if (memcmp(&g_recvBuff[1], cWoosim_4inch, sizeof(cWoosim_4inch)) == 0)
                {
                    g_wifi_printer.size = 4;
                    //fprintf(stdout, "[DEBUG] ===== Woosim WiFi Printer 4 inch =====\n");
                    g_nInQuiry = INQUIRY_NONE;
                }
            }
        }
    }
    break;
    case PRINTER_EASTROYCE:
    {
        if (g_recvBuff[0] == 0x5f)
        {
            // {0x5f, 0x45, 0x52, 0x2d, 0x35, 0x38, 0x20, 0x20, 0x00}
            if (g_nrecvCount > 8)
            {
                char cEastRoyce_2inch[12] = { 0x45, 0x52, 0x2d, 0x35, 0x38, 0x2d, 0x43, 0x4c, 0x53, 0x20, 0x20, 0x00 };
                char cEastRoyce_3inch[12] = { 0x45, 0x52, 0x2d, 0x38, 0x30, 0x2d, 0x43, 0x4c, 0x53, 0x20, 0x20, 0x00 };

                if (memcmp(&g_recvBuff[1], cEastRoyce_2inch, 5) == 0)
                {
                    g_wifi_printer.size = 2;
                    //fprintf(stdout, "[DEBUG] ===== Eastroyce WiFi Printer 2 inch =====\n");
                    if (memcmp(&g_recvBuff[6], &cEastRoyce_2inch[5], 4) == 0)
                    {
                        g_bOnlyComlaser = TRUE;
                    }
                    else
                    {
                        g_bOnlyComlaser = FALSE;
                    }
                    g_nInQuiry = INQUIRY_NONE;
                }
                else if (memcmp(&g_recvBuff[1], cEastRoyce_3inch, 5) == 0)
                {
                    g_wifi_printer.size = 3;
                    //fprintf(stdout, "[DEBUG] ===== Eastroyce WiFi Printer 3 inch =====\n");
                    if (memcmp(&g_recvBuff[6], &cEastRoyce_3inch[5], 4) == 0)
                    {
                        g_bOnlyComlaser = TRUE;
                    }
                    else
                    {
                        g_bOnlyComlaser = FALSE;
                    }
                    g_nInQuiry = INQUIRY_NONE;
                }
            }
        }
    }
    break;
    default:
    {

    }
    break;
    }
}

void SetPrinterFirmwareVer()
{

    int nManufacturer = json_data_manager_get_wifi_printer();
    switch (nManufacturer)
    {
    case PRINTER_WOOSIM_SYS:		// Woosim
    {
        if (g_recvBuff[0] == 0x1b && g_recvBuff[1] == 0x00 && g_recvBuff[2] == 0x02 && g_recvBuff[3] == 0x02)
        {
            char cWoosim_Comlaser[2] = { 0x33, 0x30 };
            if (g_nrecvCount > 10)
            {
                if (memcmp(g_recvBuff + 9, cWoosim_Comlaser, sizeof(cWoosim_Comlaser)) == 0)
                {
                    g_bOnlyComlaser = TRUE;
                    //fprintf(stdout, "[DEBUG] ===== Woosim WiFi Printer ONLY for Comlasr =====\n");
                }
                else
                {
                    g_bOnlyComlaser = FALSE;
                    //fprintf(stdout, "[DEBUG] ===== Woosim WiFi Printer for All Users =====\n");
                }
                g_nInQuiry = INQUIRY_NONE;
            }
        }
    }
    break;
    case PRINTER_EASTROYCE:
    {
    }
    break;
    default:
    {

    }
    break;
    }
}

int SendAll(int client_socket, const void *data, int data_size)
{
    const char *data_ptr = (const char*) data;
    int bytes_sent;

    while (data_size > 0)
    {
        bytes_sent = send(client_socket, data_ptr, data_size, 0);
        if (bytes_sent == -1)
            return -1;

        data_ptr += bytes_sent;
        data_size -= bytes_sent;
    }

    return 1;
}

int SendAll(int client_socket, const string &data)
{
    ulong data_size = htonl(data.size());

    int result = SendAll(client_socket, &data_size, sizeof(data_size));
    if (result == 1)
        result = SendAll(client_socket, data.c_str(), data.size());

    return result;
}

int receiveData()
{
    int nResult = 0;
    g_nrecvCount = 0;
    char recvBuff[WIFI_PRINTER_MAX_BUFFER];
    memset(recvBuff, 0, WIFI_PRINTER_MAX_BUFFER);

    nResult = recv(g_wifi_printer.socket, recvBuff, WIFI_PRINTER_MAX_BUFFER, 0);
    if (nResult > 0)
    {
        ////fprintf(stdout, "\n[DEBUG] === received Bytes : %d(mode : %d) ===\n", nResult, g_nInQuiry);
        for (int i = 0; i < nResult; i++)
        {
            ////fprintf(stdout, "(%04d) : 0x%02x\n", i, recvBuff[i]);
            g_recvBuff[g_nrecvCount + i] = recvBuff[i];
        }
        g_nrecvCount += nResult;

        switch (g_nInQuiry)
        {
        case INQUIRY_MODEL_NAME:
        {
            SetPrinterModelAndSize();
        }
        break;
        case INQUIRY_FIRMWARE_VER:
        {
            SetPrinterFirmwareVer();
        }
        break;
        }
    }
    else if (nResult == -1)
    {
        close_wifi_printer_socket();
        qDebug() << errno;
        //disp_filemanagement_main_run(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
        //fprintf(stdout, "[DEBUG] Socket Receive Error : %s\n", strerror(errno));
    }
    else if (nResult == 0)
    {
        //fprintf(stdout, "\n[DEBUG] === received Bytes : ZERO!!!! ===\n");
    }
    return nResult;
}

static void *t_wifi_read_packet(void *arg)
{
    int i = 0;
    int nResult = 0;
    g_nrecvCount = 0;
    char recvBuff[WIFI_PRINTER_MAX_BUFFER];

    // Receive data from server
    while (!g_bExitWifiThread)
    {
        if (g_wifi_printer.isConnected)
        {
            nResult = read(g_wifi_printer.socket, recvBuff, WIFI_PRINTER_MAX_BUFFER);
            if (nResult > 0)
            {
                ////fprintf(stdout, "\n[DEBUG] === received Bytes : %d(mode : %d) ===\n", nResult, g_nInQuiry);
                for (i = 0; i < nResult; i++)
                {
                    ////fprintf(stdout, "(%04d) : 0x%02x\n", i, recvBuff[i]);
                    g_recvBuff[g_nrecvCount + i] = recvBuff[i];
                }
                g_nrecvCount += nResult;

                switch (g_nInQuiry)
                {
                case INQUIRY_MODEL_NAME:
                {
                    SetPrinterModelAndSize();
                }
                break;
                case INQUIRY_FIRMWARE_VER:
                {
                    SetPrinterFirmwareVer();
                }
                break;
                }
            }
            else if (nResult == -1)
            {
                close_wifi_printer_socket();
                //disp_filemanagement_main_run(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
                //fprintf(stdout, "[DEBUG] Socket Receive Error : %s\n", strerror(errno));
            }
            else if (nResult == 0)
            {
                //fprintf(stdout, "\n[DEBUG] === received Bytes : ZERO!!!! ===\n");
            }
        }
        usleep(10 * 1000);
    }
    //fprintf(stdout, "[DEBUG] ===== WiFi Printer Receive Finished =====\n");
}

void InquiryPrinterModelInfo()
{
    char cModel_Inq[3] = { 0, };

    int nManufacturer = json_data_manager_get_wifi_printer();

    switch (nManufacturer)
    {
    case PRINTER_WOOSIM_SYS:
    {
        cModel_Inq[0] = (char)0x1b; cModel_Inq[1] = (char)0x59; cModel_Inq[2] = (char)0xff;
    }
    break;
    case PRINTER_EASTROYCE:
    {
        cModel_Inq[0] = (char)0x1d; cModel_Inq[1] = (char)0x49; cModel_Inq[2] = (char)0x43;

    }
    break;
    default:		// Woosim
    {
        cModel_Inq[0] = (char)0x1b; cModel_Inq[1] = (char)0x59; cModel_Inq[2] = (char)0xff;
    }
    break;
    }

    ClearWiFiRecvBuff(INQUIRY_MODEL_NAME);
    SendAll(g_wifi_printer.socket, cModel_Inq, 3);
//    send(g_wifi_printer.socket, cModel_Inq, 3, 0);
    int nCount = 0;
    while (TRUE)
    {
//        receiveData();

        if (g_nInQuiry == INQUIRY_NONE)
        {
            //fprintf(stdout, "\n[DEBUG] === Out of InquiryPrinterModelInfo on INQUIRY_NONE ===\n");
            break;
        }

        nCount++;
        if (nCount == 3000) // check for 3 secs
        {
            //fprintf(stdout, "\n[DEBUG] === Out of InquiryPrinterModelInfo after 3 seconds ===\n");
            break;
        }
        usleep(1000);
    }





}

void InquiryPrinterFirmwareInfo()
{
    char cFW_Inq[4] = { 0, };

    int nManufacturer = json_data_manager_get_wifi_printer();

    //fprintf(stdout, "\n[DEBUG] === InquiryPrinterFirmwareInfo Manufacturer : %d ===\n", nManufacturer);
    switch (nManufacturer)
    {
    case PRINTER_WOOSIM_SYS:
    {
        cFW_Inq[0] = (char)0x1b; cFW_Inq[1] = (char)0x00; cFW_Inq[2] = (char)0x02; cFW_Inq[3] = (char)0x02;
        ClearWiFiRecvBuff(INQUIRY_FIRMWARE_VER);
        SendAll(g_wifi_printer.socket, cFW_Inq, 4);
//        receiveData();

//        send(g_wifi_printer.socket, cFW_Inq, 4, 0);
    }
    break;
    case PRINTER_EASTROYCE:
    {
        ClearWiFiRecvBuff(INQUIRY_NONE);
        //cFW_Inq[0] = (char)0x1d; cFW_Inq[1] = (char)0x49; cFW_Inq[2] = (char)0x43;
    }
    break;
    }

    int nCount = 0;
    while (TRUE)
    {

        if (g_nInQuiry == INQUIRY_NONE)
        {
            //fprintf(stdout, "\n[DEBUG] === Out of Inquiry Printer Firmware Info on INQUIRY_NONE ===\n");
            break;
        }

        nCount++;
        if (nCount == 3000) // check for 3 secs
        {
            //fprintf(stdout, "\n[DEBUG] === Out of Inquiry Printer Firmware Info after 3 seconds ===\n");
            break;
        }
        usleep(1000);
    }



}

int connect_wifi_printer()
{
    int i = 0;
    int nRet = 0;
    int sock = 0;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    char strIP1[8] = { 0, }; memset(strIP1, 0, 8);
    char strIP2[8] = { 0, }; memset(strIP2, 0, 8);
    char strIP3[8] = { 0, }; memset(strIP3, 0, 8);

    char strIP[128] = { 0, };
    int ip1 = 192;//json_data_manager_get_ip_address_1();
    int ip2 = 168;//json_data_manager_get_ip_address_2();
    int ip3 = 0;//json_data_manager_get_ip_address_3();
    sprintf(strIP, "%d.%d.%d.19", ip1, ip2, ip3);
    //fprintf(stdout, "\n=== IP : %s\n\n", strIP);

    serv_addr.sin_addr.s_addr = inet_addr(strIP);

    serv_addr.sin_port = htons(9100);

    int nSucc = -1;
    if (g_wifi_printer.isConnected)
    {
        close_wifi_printer_socket();
    }

    g_wifi_printer.socket = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        //fprintf(stdout, "Cannot Create Socket!!!\n");
    }
    else
    {
        g_bOnlyComlaser = FALSE;
        memcpy(g_wifi_printer.serv_addr, &serv_addr, sizeof(serv_addr));
        nSucc = connect_with_timeout(g_wifi_printer.socket, serv_addr, 2000);
        if (nSucc == 0)
        {
            g_wifi_printer.isConnected = TRUE;

            usleep(100 * 1000);
            InquiryPrinterFirmwareInfo();
            InquiryPrinterModelInfo();

            if (g_bOnlyComlaser)
            {
                //fprintf(stdout, "===== Connection Is for Comlaser ONLY =====\n");
            }
            else
            {
                //fprintf(stdout, "===== Connection Is NOT for Comlaser ONLY =====\n");
                close_wifi_printer_socket();
            }
            nRet = 1;
        }
        else
        {
            //fprintf(stdout, "===== Connection Is Failed =====\n");
            close_wifi_printer_socket();
        }
    }
    return nRet;
}

void WiFi_Printf(int sock, char* fmt, ...)
{
    int nLen = 0;
    char buffer[2048] = { 0 };
    va_list ap;

    va_start(ap, fmt);
    nLen = vsprintf(buffer, fmt, ap);
    va_end(ap);

    if (g_wifi_printer.isConnected)
    {
        //int nWrotten = write(sock, buffer, nLen + 1);
        int nWrotten = send(sock, buffer, nLen + 1, 0);
        //fprintf(stdout, "(%d)%s", nWrotten, buffer);
        if (nWrotten == -1)
        {
            close_wifi_printer_socket();
            // Make the CONNECT button disabled
        }
    }
}

//static int parse_filename(char *filename)
//{
//    int nCount = 0;
//    char *result;

//    if (filename == NULL)
//    {
//        //fprintf(stdout, "=== Pasering Error : File name is NULL ===\n");
//    }
//    else
//    {
//        result = strtok(filename, "_");
//        while (result != NULL)
//        {
//            //fprintf(stdout, "=== Parsering : %s ===\n", result);
//            switch (nCount)
//            {
//            case 0: // prefix
//            {
//                if (!strncmp(result, "AI", 2))
//                {
//                    sprintf(g_file_elem_for_printer.prefix, "%s", "AI");
//                }
//                else if (!strncmp(result, "AV", 2))
//                {
//                    sprintf(g_file_elem_for_printer.prefix, "%s", "AV");
//                }
//                else if (!strncmp(result, "VV", 2))
//                {
//                    sprintf(g_file_elem_for_printer.prefix, "%s", "VV");
//                }
//                else if (!strncmp(result, "MC", 2))
//                {
//                    sprintf(g_file_elem_for_printer.prefix, "%s", "MC");
//                }
//            }
//            break;
//            case 1: // file index
//            {
//                sprintf(g_file_elem_for_printer.file_id, "%s", result);
//            }
//            break;
//            case 2: // date
//            {
//                char year[5] = { 0 }; char month[3] = { 0 }; char day[3] = { 0 };

//                year[0] = result[0]; year[1] = result[1]; year[2] = result[2]; year[3] = result[3];
//                month[0] = result[4]; month[1] = result[5];
//                day[0] = result[6]; day[1] = result[7];

//                sprintf(g_file_elem_for_printer.year, "%s", year);
//                sprintf(g_file_elem_for_printer.month, "%s", month);
//                sprintf(g_file_elem_for_printer.day, "%s", day);
//            }
//            break;
//            case 3: // time
//            {
//                char hour[3] = { 0 }; char minute[3] = { 0 }; char sec[3] = { 0 }; char msec[2] = { 0 };
//                hour[0] = result[0]; hour[1] = result[1];
//                minute[0] = result[2]; minute[1] = result[3];
//                sec[0] = result[4]; sec[1] = result[5];
//                msec[0] = result[6];

//                sprintf(g_file_elem_for_printer.hour, "%s", hour);
//                sprintf(g_file_elem_for_printer.minute, "%s", minute);
//                sprintf(g_file_elem_for_printer.second, "%s", sec);
//                sprintf(g_file_elem_for_printer.msec, "%s", msec);
//            }
//            break;
//            case 4: // laser captured speed
//            {
//                sprintf(g_file_elem_for_printer.laser_capture_speed, "%s", result);
//            }
//            break;
//            case 5: // display speed limit
//            {
//                sprintf(g_file_elem_for_printer.display_limit_speed, "%s", result);
//            }
//            break;
//            case 6: // capture speed limit
//            {
//                sprintf(g_file_elem_for_printer.capture_limit_speed, "%s", result);
//            }
//            break;
//            case 7: // captured distance
//            {
//                sprintf(g_file_elem_for_printer.laser_capture_distance, "%s", result);
//            }
//            break;
//            case 8: // user mode, enforcement mode, dual mode, zoom level
//            {
//                char user_mode[2] = { 0, }; char enforce_mode[2] = { 0, };
//                char dual_mode[2] = { 0, }; char zoom_level[2] = { 0, };
//                user_mode[0] = result[0]; enforce_mode[0] = result[1];
//                dual_mode[0] = result[2]; zoom_level[0] = result[3];
//                sprintf(g_file_elem_for_printer.user_mode, "%s", user_mode);
//                sprintf(g_file_elem_for_printer.enforcement_mode, "%s", enforce_mode);
//                sprintf(g_file_elem_for_printer.dual_mode, "%s", dual_mode);
//                sprintf(g_file_elem_for_printer.zoom_level, "%s", zoom_level);
//            }
//            break;
//            case 9: // latitude
//            {
//                sprintf(g_file_elem_for_printer.latitude, "%s", result);
//            }
//            break;
//            case 10: // longitude
//            {
//                sprintf(g_file_elem_for_printer.longitude, "%s", result);
//            }
//            break;
//            case 11: // location
//            {
//                sprintf(g_file_elem_for_printer.location, "%s", result);
//            }
//            break;
//            case 12: // user name
//            {
//                sprintf(g_file_elem_for_printer.user_name, "%s", result);
//            }
//            break;
//            case 13: // device id
//            {
//                sprintf(g_file_elem_for_printer.device_id, "%s", result);
//            }
//            break;
//            case 14: // unit
//            {
//                sprintf(g_file_elem_for_printer.unit, "%c", result[0]);
//            }
//            break;
//            }
//            nCount++;
//            result = strtok(NULL, "_");
//        }
//    }
//    return nCount;
//}

int json_data_manager_get_ip_address_1()
{
    ConfigManager configManager = ConfigManager("parameter_setting4.json");
    QJsonObject JsonObject = configManager.GetConfig();
    //TRACE_JSON("json_data_manager_get_ip_address_1");
    //strcpy(str_ip_address_1, s_st_json_setting_network.ip_address_1);

    return TRUE;
}

int json_data_manager_get_ip_address_2()
{
    ConfigManager configManager = ConfigManager("parameter_setting4.json");
    QJsonObject JsonObject = configManager.GetConfig();
    return TRUE;
}

int json_data_manager_get_ip_address_3()
{

    ConfigManager configManager = ConfigManager("parameter_setting4.json");
    QJsonObject JsonObject = configManager.GetConfig();
    return TRUE;
}

int json_data_manager_get_wifi_printer()
{
    ConfigManager configManager = ConfigManager("print_option.json");
    QJsonObject jsonObject = configManager.GetConfig();
    return jsonObject["Manufacturer"].toInt();
}

bool json_data_manager_get_print_option_body()
{
    ConfigManager configManager = ConfigManager("print_option.json");
    QJsonObject jsonObject = configManager.GetConfig();
    return jsonObject["printOption_body"].toBool();
}
bool json_data_manager_get_print_option_logo()
{
    ConfigManager configManager = ConfigManager("print_option.json");
    QJsonObject jsonObject = configManager.GetConfig();
    return jsonObject["print_on_logo"].toBool();

}
bool json_data_manager_get_print_option_ticket_num()
{
    ConfigManager configManager = ConfigManager("print_option.json");
    QJsonObject jsonObject = configManager.GetConfig();
    return jsonObject["printOption_ticket_num"].toBool();

}
