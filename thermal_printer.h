/*-------------------------- [ Comment ] --------------------------------*\
File name	: thermal_printer.h
Project		: Comlaser H20
Description :

Copyright(c) 2018-2040, Comlaser CO., LTD. All rights reserved.
-----------------------------------------------------------------------
C0000 - Created by shkang@nextchip.com		2018-12-26
C0001 -
\*-----------------------------------------------------------------------*/
#ifndef	__THERMAL_PRINTER_H__
#define	__THERMAL_PRINTER_H__
//#include "base.h"
//#include "config.h"
#include <pthread.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define WIFI_PRINTER_MAX_BUFFER					4096
#define DEVICE_ID_MAX_LENGTH							7
#define USER_NAME_MAX_LENGTH							13
#define LOCATION_MAX_LENGTH								25

/*
typedef struct {
    int 	prefix;											// 0 : not selected, 1 : AI, 2 : AV, 3 : VV, 4 : MC
    int		file_id;										//00001
    int		year;											//2018
    int		month;											//12
    int		day;											//11
    int		hour;											//23
    int		minute;											//15
    int		second;											//49
    int		msec;											//1/10 sec
    float	laser_capture_speed;							//+9999 (km/h or MPH)
    float	display_limit_speed;							//9999 (km/h or MPH)
    float	capture_limit_speed;							//9999 (km/h or MPH)
    float	laser_capture_distance;							//9999 (meter or feet)
    char	user_mode;										// 0 : (user mode off), 1 : (user mode on), 2 : (video mode)
    char	enforcement_mode;								// 0 : (image only), 1 : (image + video), 2 : (video only)
    char	dual_mode;										// 0 : (normal), 1 : (truck)
    char	zoom_level;										//01~11 (zoom level)
    float	latitude;										//+37.347327
    float	longitude;										//+126.955778
    char	location[LOCATION_MAX_LENGTH + 1];				//SEOUL
    char	user_name[USER_NAME_MAX_LENGTH + 1];			//Mike
    char	device_id[DEVICE_ID_MAX_LENGTH + 1];			//TP00001
    int		unit;											// 1 : Standard unit(km/h, m), 2 : British unit (mph, feet)
} ST_ENFORCEMENT_INFO_ELEMENT;
*/
typedef struct {
    char 	prefix[2+1];									//AI, AV, VV
    char	file_id[5+1];									//00001
    char	year[4+1];										//2018
    char	month[2+1];										//12
    char	day[2+1];										//11
    char	hour[2+1];										//23
    char	minute[2+1];									//15
    char	second[2+1];									//49
    char	msec[1+1];										//1/10 sec
    char	laser_capture_speed[5+1];						//+9999 (km/h or MPH)
    char	display_limit_speed[4+1];						//9999 (km/h or MPH)
    char	capture_limit_speed[4+1];						//9999 (km/h or MPH)
    char	laser_capture_distance[4+1];					//9999 (meter or feet)
    char	user_mode[1+1];									//N (user mode off), U(user mode on), V(video mode)
    char	enforcement_mode[1+1];							//I (image only), A(image + video), V(video only)
    char	dual_mode[1+1];									//N (normal), T (truck)
    char	zoom_level[2+1];								//01~11 (zoom level)
    char	latitude[10+1];									//+37.347327
    char	longitude[11+1];								//+126.955778
    char	location[LOCATION_MAX_LENGTH+1];				//SEOUL
    char	user_name[USER_NAME_MAX_LENGTH+1];				//Mike
    char	device_id[DEVICE_ID_MAX_LENGTH+1];				//TP00001
    char	unit[1+1];										//S: Standard unit(km/h, m), B: British unit (mph, feet)
} ST_ENFORCEMENT_FILENAME_ELEMENT;


typedef enum _PRINTER_MANUFACTURER {
    PRINTER_WOOSIM_SYS = 0,
    PRINTER_EASTROYCE,
}PRINTER_MANUFACTURER;

typedef enum _PRINTER_INQUIRY {
    INQUIRY_NONE = 0,
    INQUIRY_MODEL_NAME,
    INQUIRY_FIRMWARE_VER,
}PRINTER_INQUIRY;

typedef struct _st_WIFI_PRINTER{
    int		socket;
    struct sockaddr_in *serv_addr;
    int		size;
    int		manufacturer;
    bool	connected_once;
    bool	isConnected;
} ST_WIFI_PRIINTER;

//class ThermalPrinter
//{
//public:
//    ThermalPrinter();
//    virtual ~ThermalPrinter();



//};
    void print_wifi_printer(/*char *fullfilename*/);
    void print_wifi_header(int socket);
    void print_wifi_body(int socket);
    int connect_wifi_printer();
    void close_wifi_printer_socket();
    void CreateWiFiReadThreadAndInitPrinter(void);
    void WiFi_Printf(int sock, char* fmt, ...);
//    void print_wifi_printer(char *fullfilename);
    //void json_data_manager_get_wifi_printer();
    int json_data_manager_get_ip_address_1();
    int json_data_manager_get_ip_address_2();
    int json_data_manager_get_ip_address_3();
    int json_data_manager_get_wifi_printer();
    bool json_data_manager_get_print_option_body();
    bool json_data_manager_get_print_option_logo();
    bool json_data_manager_get_print_option_ticket_num();
    void print_wifi_header_office_txt_info(int socket);
    void InquiryPrinterFirmwareInfo();
    void SetPrinterFirmwareVer();
    void InquiryPrinterModelInfo();

extern bool g_bOnlyComlaser;
extern ST_WIFI_PRIINTER g_wifi_printer;
extern char g_print_img_body_buff_file_management[1712 * 984];  // Only Y among YUV 420 image body buffer for thermal printer from uncompressed jpg file
extern char g_print_img_body_buff_file_logo[1712 * 984];  // David, Add for LOGO file
extern ST_ENFORCEMENT_FILENAME_ELEMENT g_file_elem_for_printer;


#endif //__THERMAL_PRINTER_H__
