//------------------------------------------------------------------------------
//  Serial 송/수신 패킷 [Encode / Decode] 라이브러리
#include <stdio.h>
#include <string.h>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include "ViscaPacket.h"
#include "Logger.h"

QString g_Optical_Zoom_Value_KTNC[NUMBER_OPTICAL_ZOOM_CNT]=
{
    "0000", //x1
    "1777", //x2
    "2183",
    "279B",
    "2BCB",
    "2F10",
    "317D",
    "33A0",
    "357D",
    "371D",
    "388C",
    "39CB",
    "3ADF",
    "3BCB",
    "3C93",
    "3D39",
    "3DC5",
    "3E3C",
    "3E9C",
    "3EED",
    "3F16",
    "3F3E",
    "3F60",
    "3F7C",
    "3F97",
    "3FB0",
    "3FC3",
    "3FD6",
    "3FEA",//x29
    "4000"//x30
};

int g_Digital_Zoom_X_Asix_KTNC[NUMBER_DZOOM_CNT] = {
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12
};

//seperate mode
QString g_Digital_Zoom_Y_ASIX_KTNC[NUMBER_DZOOM_CNT]=
{
    "00",
    "80",
    "AA",
    "C0",
    "CC",
    "D5",
    "DB",
    "E0",
    "E3",
    "E6",
    "E8",
    "EB"
};

QString g_Iris_Y_ASIX_KTNC[NUMBER_IRIS_CNT] =
{
    "11 open", //open
    "10",
    "0F",
    "0E",
    "0D",
    "0C",
    "0B",
    "0A",
    "09",
    "08",
    "07",
    "06",
    "05",
    "04",
    "03",
    "02",
    "01",
    "00 close", //close
};


QString g_Shutter_Y_ASIX_KTNC[NUMBER_SHUTTER_CNT] =
{
    "15",
    "14",
    "13",
    "12",
    "11",
    "10",
    "0F",
    "0E",
    "0D",
    "0C",
    "0B",
    "0A",
    "09",
    "08",
    "07",
    "06",
    "05",
    "04",
    "03",
    "02",
    "01",
    "00"
};

QString g_Shutter_X_ASIX_KTNC[NUMBER_SHUTTER_CNT] =
{
    "1/10000(100us)",
    "1/6000(167us)",
    "1/4000(250us)",
    "1/3000(333us)",
    "1/2000(500us)",
    "1/1500(670us)",
    "1/1000(1 ms)",
    "1/725 (1.3 ms)",
    "1/500 (2 ms)",
    "1/350 (3 ms)",
    "1/250 (5 ms)",
    "1/180 (6 ms",
    "1/125 (8 ms)",
    "1/100 (10 ms)",
    "1/90  (11 ms)",
    "1/60  (16 ms)",
    "1/30  (33 ms)",
    "1/15  (66 ms) ",
    "1/8   (125 ms)",
    "1/4   (250 ms)",
    "1/2   (500 ms)",
    "1/1"
};

QString g_Gain_Y_ASIX_KTNC[NUMBER_GAIN_CNT_KTNC]= //
{
    "00 (-3dB)",
    "01 (+0dB)",
    "02 (+4dB)",
    "03 (+8dB)",
    "04 (+12dB)",
    "05 (+16dB)",
    "06 (+20dB)",
    "07 (+24dB)",
    "08 (+28dB)",
    "09 (+32dB)",
    "0A (+36dB)",
    "0B (+40dB)",
    "0C (+44dB)",
    "0D (+48dB)",
    "0E (+52dB)",
    "0F (+58dB)",

};
#if 1 //wonwoo camera
QString g_Optical_Zoom_Value_Wonwoo[NUMBER_OPTICAL_ZOOM_CNT]=
{
    "0000", //x1
    "10BE", //x2
    "1B66",
    "2258",
    "2729",
    "2AC1",
    "2D88",
    "2FCE",
    "31B9",
    "3360",
    "34DC",
    "362D",
    "3760",
    "387A",
    "397C",
    "3A6B",
    "3B3B",
    "3BF9",
    "3CA5",
    "3D38",
    "3DB9",
    "3E27",
    "3E83",
    "3ED9",
    "3F23",
    "3F60",
    "3F97",
    "3FC8",
    "3FED",//x29
    "4000"//x30
};

int g_Digital_Zoom_X_Asix_Wonwoo[24] = {
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12,
   13,
   14,
   15,
   16,
   17,
   18,
   19,
   21,
   23,
   25,
   28,
   32
};

//seperate mode
QString g_Digital_Zoom_Y_ASIX_Wonwoo[24]=
{
    "00",
    "80",
    "AA",
    "C0",
    "CC",
    "D5",
    "DB",
    "E0",
    "E3",
    "E6",
    "E8",
    "EB",
    "ED",
    "EE",
    "EF",
    "F0",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8"
};

QString g_Iris_Y_ASIX_Wonwoo[NUMBER_IRIS_CNT] =
{
    "11 open", //open
    "10",
    "0F",
    "0E",
    "0D",
    "0C",
    "0B",
    "0A",
    "09",
    "08",
    "07",
    "06",
    "05",
    "00 close", //close
};


QString g_Shutter_Y_ASIX_Wonwoo[NUMBER_SHUTTER_CNT] =
{
    "0D",
    "0C",
    "0B",
    "0A",
    "09",
    "08",
    "07",
    "06",
    "05",
    "04",
    "03",
    "02",
    "01",
    "00",
};

QString g_Shutter_X_ASIX_Wonwoo[NUMBER_SHUTTER_CNT] =
{
    "1/30000(0.03ms)",
    "1/10000(0.1 ms)",
    "1/7000(0.15 ms)",
    "1/5000(0.2 ms)",
    "1/2500(0.4 ms)",
    "1/1600(0.6 ms)",
    "1/1000(1  ms)",
    "1/700 (1.5 ms)",
    "1/250 (4  ms)",
    "1/120 (8  ms)",
    "1/60  (16 ms)",
    "1/30  (33 ms)",
    "1/15  (66 ms) ",
    "1/8   (125ms)",
};

QString g_Gain_Y_ASIX_Wonwoo[NUMBER_GAIN_CNT_WONWOO]= //
{
    "00 (00dB)",
    "01 (08dB)",
    "02 (13dB)",
    "03 (17dB)",
    "04 (22dB)",
    "05 (27dB)",
    "06 (32dB)",
    "07 (37dB)",
    "08 (41dB)",
    "09 (46dB)",
    "0A (51dB)"
};
#endif

int g_Camera_VenderID = 0x0078;
QByteArray send_header_data;

//------------------------------------------------------------------------------
//  Private : 송신 패킷의 형태로 인코딩
//Head - 1xxx0kkk
void ViscaPacket::BlockCamEncodePacket(unsigned char TotalMsgLen,
                   unsigned char Head,
                   unsigned char *Msg,
                   QByteArray *send)
{
    unsigned char i;

    // HEADER 삽입
    g_TxLength = 0;
    g_TxBuf[g_TxLength] = Head; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    // Message 삽입
    for (i = 0; i < TotalMsgLen; i++)
    {
        g_TxBuf[g_TxLength] = Msg[i];send->push_back(g_TxBuf[g_TxLength]);  g_TxLength++;
    }

    // Terminator 삽입
    g_TxBuf[g_TxLength] = 0xFF; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

}
//------------------------------------------------------------------------------
//  Public : 사용자가 새로운 송신할 패킷을 만든다.
//
QByteArray ViscaPacket::BlockCamMakePacket( unsigned char Head, unsigned char *Msg, unsigned char MsgSize )
{
    QByteArray send;
    send.clear();
    if ( MsgSize <= MAX_PACKET_BLOCK_DATA )
    {

        BlockCamEncodePacket( MsgSize,
                      Head,
                      Msg ,
                      &send);
//      original
//        if(Msg[1]==0x01 && Msg[2]==0x04)
//        {
//            //command
//        }

//        if(Msg[1]==0x09 && (Msg[2]==0x00||Msg[2]==0x04||Msg[2]==0x05) )
//        {
//            send_header_data.push_back(Msg[2]);
//        }

        if(Msg[0]==0x01 && Msg[1]==0x04)
        {
            //command
        }

        if(Msg[0]==0x09 && (Msg[1]==0x00||Msg[1]==0x04||Msg[1]==0x05) )
        {
            send_header_data.push_back(Msg[2]);//tnwjd 2->3
        }
        return send;
    }
    return send;
}


//response
//[ACK]
//Type: Normal
//Response: 0xX0 0x4x 0xFF
//			X = 0x08 | responding device# (0x09..0x0F)
//			x = responding device# (0x00..0x07)

//[Complete]
//Type: Normal
//Response: 0xX0 0x5x 0xFF
//			X = 0x08 | responding device# (0x09..0x0F)
//			x = responding device# (0x00..0x07)

//[Error]
//Type: Normal
//Response: 0xX0 0x6x NN 0xFF
//			X = 0x08 | responding device# (0x09..0x0F)
//			x = responding device# (0x00..0x07)
//			NN = error code
//			0x01 = Message length error (>14 bytes)
//			0x02 = Syntax error
//			0x03 = Command buffer error
//			0x04 = Command cancelled
//			0x05 = No socket
//			0x40 = Power off
//			0x41 = Command failed
//			0x42 = Search error
//			0x43 = Condtion error
//			0x46 = Counter type error
//			0x47 = Tuner error
//			0x48 = Emergency stop error
//			0x49 = Media unmounted
//			0x4A = Register error
//			0x4B = Register mode setting error

unsigned char	ViscaPacket::CheckRcvMsg(unsigned char RxData)
{
    static unsigned char RxLength = 0, stx=0, info_flag=0;

    if(RxLength >= 14)
    {
        memset(g_RxBuf, 0, sizeof(unsigned char) *MAX_PACKET_SIZE);
        g_RxLength = 0;
        RxLength=0;
        stx=0;
        info_flag=0;
        return 0;
    }

    if(RxData == 0xFF && stx==1) //패킷 끝
    {
        g_RxBuf[RxLength] = RxData;
        RxLength++;

        g_RxLength = RxLength;

        RxLength=0;
        stx=0;

        //dump
        //for(int i=0; i< g_RxLength;i++)
        //	info.sprintf("Debug_Dump[%02d]: %02X",i, g_RxBuf[i] );

        if(info_flag ==1 || info_flag ==3 || info_flag ==4)
        {
            info_flag=0;
            return 1;
        }
        else if(info_flag ==0)
        {
            return 0;
        }
        else //info_flag ==2
        {
            info_flag=0;
            return 2;//응답조건 COMPELETE_INQUIRES
        }
    }
    else
    {
        if( (RxData & 0x90) == 0x90 && stx==0) //start
        {
            stx=1;
            g_RxBuf[RxLength] = RxData;
            RxLength++;
            return 0;
        }

        if(stx==1)
        {
            g_RxBuf[RxLength] = RxData;
            RxLength++;

            if(info_flag==0 && RxLength==2)
            {
                if( (RxData)  == RECEVIE_ACK)//ack
                {
                    info_flag=1;
                }
                else if( (RxData) == COMPELETE_INQUIRES)//complete(inquiries)
                {
                    info_flag=2;
                }
                else if( (RxData ) == ERROR)//error
                {
                    info_flag=3;
                }
                else if( (RxData) == COMPELETE_COMMAND)////complete(command)
                {
                    info_flag=4;
                }                
            }
            else
            {
                if(info_flag==3) //error
                {
                    QString error;
                    if(RxData==0x01)
                    {
                        error.sprintf("%s","Message length error (>14 bytes)");
                    }
                    else if(RxData==0x02)
                    {
                        error.sprintf("%s","Syntax error");
                    }
                    else if(RxData==0x03)
                    {
                        error.sprintf("%s", "Command buffer error");
                    }
                    else if(RxData==0x04)
                    {
                        error.sprintf("%s", "Command cancelled");
                    }
                    else if(RxData==0x05)
                    {
                        error.sprintf("%s", "No socket");
                    }
                    else if(RxData==0x40)
                    {
                        error.sprintf("%s", "Power off");
                    }
                    else if(RxData==0x41)
                    {
                        error.sprintf("%s", "Command failed");
                    }
                    else if(RxData==0x42)
                    {
                        error.sprintf("%s", "Search error");
                    }
                    else if(RxData==0x43)
                    {
                        error.sprintf("%s", "Condtion error");
                    }
                    else if(RxData==0x46)
                    {
                        error.sprintf("%s", "Counter type error");
                    }
                    else if(RxData==0x47)
                    {
                        error.sprintf("%s", "Tuner error");
                    }
                    else if(RxData==0x48)
                    {
                        error.sprintf("%s", "Emergency stop error");
                    }
                    else if(RxData==0x49)
                    {
                        error.sprintf("%s", "Media unmounted");
                    }
                    else if(RxData==0x4A)
                    {
                        error.sprintf("%s", "Register error");
                    }
                    else if(RxData==0x4B)
                    {
                        error.sprintf("%s", "Register mode setting error");
                    }
                    qDebug() << error;

                }
                else if(info_flag==2)
                {
                    ;
                }
                else if(info_flag==1)
                {
                    QString response;
                    response.sprintf("%s", "RESPONSE_ACK");
                    qDebug() << response;
                }
            }
        }
    }
    return 0;
}


//------------------------------------------------------------------------------------
//	수신된 하나의 패킷에 대하여 유효성 검사
//	[Return Value]
//		0 : 비정상 패킷
//		1 : 정상 패킷
//------------------------------------------------------------------------------------
unsigned char	ViscaPacket::MsgDecoder()
{
    if(send_header_data.isEmpty())
        return 0;

    send_data = send_header_data[0];
    //cnrk
    send_header_data.remove(0, 1);
    QString info;

    if(send_data == 0x47) //zoom position
    {
        g_ZoomPos.p = g_RxBuf[2] & 0x0F;
        g_ZoomPos.q = g_RxBuf[3] & 0x0F;
        g_ZoomPos.r = g_RxBuf[4] & 0x0F;
        g_ZoomPos.s = g_RxBuf[5] & 0x0F;
        m_zoomPQRS = (g_ZoomPos.p << 12) | (g_ZoomPos.q <<8) | (g_ZoomPos.r << 4) | (g_ZoomPos.s <<0);
        info.sprintf("Zoom position(%X):%02X; %02X; %02X; %02X", m_zoomPQRS, g_ZoomPos.p, g_ZoomPos.q, g_ZoomPos.r, g_ZoomPos.s);
        qDebug() << info;
        m_qstrZoom_pqrs = QString::number(m_zoomPQRS, 16);
        emit sig_show_zoom(m_qstrZoom_pqrs);
        SetLogMsg(VISCA_RECEIVE_DATA, QString("show_zoomPosition(" + m_qstrZoom_pqrs + ")"));

        return 1;
    }
    else if(send_data == 0x06) //dzoom on / off
    {
        if(g_RxBuf[2]==0x02)
            g_DZoomOnOff =1;
        else
            g_DZoomOnOff =0;

       info.sprintf("Dzoom on(1) / off(0): %02X", g_DZoomOnOff);
       qDebug() << info;

       return 1;
    }
    else if(send_data == 0x36) //dzoom mode
    {
        if(g_RxBuf[2]==0x00)
            g_DZoomMode= 0;//combine
        else
            g_DZoomMode=1; //seperate

        info.sprintf("DZoom mode combine(0) / seperate(1): %02X", g_DZoomMode);
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x46) //dzoom pos
    {
        g_DZoomPos.p = g_RxBuf[4];
        g_DZoomPos.q = g_RxBuf[5];
        m_DZoom =(g_DZoomPos.p << 4) | (g_DZoomPos.q << 0);
        info.sprintf("DZoom pos (%02X)_%02X; %02X", m_DZoom, g_DZoomPos.p, g_DZoomPos.q);
        m_qstrDZoom_pqrs = QString::number(m_DZoom, 16);
        qDebug() << info;
        emit sig_show_dzoom(m_qstrDZoom_pqrs);
        return 2;
    }
    else if(send_data == 0x38) //focus mode
    {
        if(g_RxBuf[2]==0x02)
            g_FocusMode =1;//auto focus
        else
            g_FocusMode =0; //manual

        info.sprintf("Focus mode manual(0) / auto(1): %02X", g_FocusMode);
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x48) //focus position
    {
        g_FocusPos.p = g_RxBuf[2];
        g_FocusPos.q = g_RxBuf[3];
        g_FocusPos.r = g_RxBuf[4];
        g_FocusPos.s = g_RxBuf[5];
        m_focusPQRS = (g_FocusPos.p << 12) | (g_FocusPos.q <<8) | (g_FocusPos.r << 4) | (g_FocusPos.s <<0);
        info.sprintf("Focus position(%X):%02X ;%02X; %02X; %02X", m_focusPQRS, g_FocusPos.p, g_FocusPos.q, g_FocusPos.r, g_FocusPos.s);        
        qDebug() << info;
        //feedback
        m_qstrFocus_pqrs = QStringLiteral("%1").arg(m_focusPQRS, 4, 16, QLatin1Char('0'));

        emit sig_show_focus(m_qstrFocus_pqrs);
        SetLogMsg(VISCA_RECEIVE_DATA, QString("show_focusPosition(" + m_qstrFocus_pqrs + ")"));

        return 1;
    }
    else if(send_data == 0x35) //WB mode
    {
        g_WBMode = g_RxBuf[2];

        info.sprintf("WB mode (00=AUTO, 01=In, 02=Out):%02X", g_WBMode);
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x53) //NR mode(noise reduction mode)
    {
        g_NRMode = g_RxBuf[2];

        info.sprintf("NR mode (0p, p:0 to 5):%02X", g_NRMode);
        qDebug() << info;
        emit sig_show_DNR(QStringLiteral("%1").arg(g_NRMode, 2, 16, QLatin1Char('0')));
        return 1;
    }
    else if(send_data == 0x39) //AE mode
    {
        g_AEMode = g_RxBuf[2];
        info.sprintf("AE mode (00=AUTO, 03=Maual, 0A=SP, 0B=IP, 0X=BP):%02X", g_AEMode);
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x4A) //shutter pos
    {
        g_ShutterPos.p = g_RxBuf[4];
        g_ShutterPos.q = g_RxBuf[5];

        m_shutter = (g_ShutterPos.p << 4) | (g_ShutterPos.q <<0);
        info.sprintf("Shutter Position(%02X)_%02X; %02X", m_shutter, g_ShutterPos.p, g_ShutterPos.q);
        qDebug() << info;
        //feedback
        m_qstrShutter_pq = QStringLiteral("%1").arg(m_shutter, 2, 16, QLatin1Char('0'));
        emit sig_show_shutter();
        emit sig_show_shutter(m_qstrShutter_pq);
        return 1;
    }
    else if(send_data == 0x4B) //iris pos
    {
        g_IrisPos.p = g_RxBuf[4];
        g_IrisPos.q = g_RxBuf[5];
        m_iris = (g_IrisPos.p << 4) | (g_IrisPos.q <<0);
        info.sprintf("Iris Position(%02X)_ %02X; %02X",  m_iris, g_IrisPos.p, g_IrisPos.q);
        //feedback
        m_qstrIris_pq = QStringLiteral("%1").arg(m_iris, 2, 16, QLatin1Char('0'));
        qDebug() << info;
        emit sig_show_iris();
        emit sig_show_iris(m_qstrIris_pq);
        return 1;
    }
    else if(send_data == 0x4C) //Gain pos
    {
        g_GainPos.p = g_RxBuf[4];
        g_GainPos.q = g_RxBuf[5];
        m_gain = (g_GainPos.p << 4) | (g_GainPos.q <<0);
        info.sprintf("Gain Position(%02X)_%02X; %02X",  m_gain, g_GainPos.p, g_GainPos.q);
        qDebug() << info;
        emit sig_show_gain(QStringLiteral("%1").arg(m_gain, 2, 16, QLatin1Char('0')));
        return 1;
    }
    else if(send_data == 0x4D) //Bright pos
    {
        g_BrightPos.p = g_RxBuf[4];
        g_BrightPos.q = g_RxBuf[5];
        info.sprintf("Bright Position(%02X) %02X; %02X",  (g_BrightPos.p << 4) | (g_BrightPos.q <<0), g_BrightPos.p, g_BrightPos.q);
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x51) //auto icr on off?
    {
        info.sprintf("auto ICR on(0x02)/off(0x03): %02X", g_RxBuf[2] );
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x01) //icr on off?
    {
        info.sprintf("ICR on(0x02)/off(0x03): %02X", g_RxBuf[2] );
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x28) //Focus Near Limit
    {
        info.sprintf("Focus Near Limit Pos(qprs) : %02X %02X %02X %02X", g_RxBuf[2], g_RxBuf[3], g_RxBuf[4], g_RxBuf[5] );
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x58) //AF Sensitivity?
    {
        info.sprintf("AF Sensitivity Normal(0x02)/Low(0x03) : %02X", g_RxBuf[2] );
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x57) //AF Mode?
    {
        info.sprintf("AF Mode Normal(0x00)/Interval(0x01)/Zoom Trigger(0x02) : %02X", g_RxBuf[2] );
        qDebug() << info;
        return 1;
    }
    else if(send_data == 0x27) //AF Time Setting?
    {
        info.sprintf("AF Time Setting(qprs) : %02X %02X %02X %02X", g_RxBuf[2], g_RxBuf[3], g_RxBuf[4], g_RxBuf[5] );
         qDebug() << info;
        return 1;
    }
    else if (send_data == 0x11) // IR Correction?
    {
        info.sprintf("IR Correction : Standard(0x00)/IR Light(0x01) : %02X", g_RxBuf[2] );
        qDebug() << info;
        return 1;
    }
    else if (send_data == 0x3d) // Wide Dynamic mode?
    {
        info.sprintf("WD : WD(0x02)/Off(0x03)/AutoOnOff(0x00)/RFix(0x01)/DverOpr(0x04) : %02X", g_RxBuf[2] );        
        qDebug() << info;
        return 1;
    }
    else if (send_data == 0x34) // DIS Mode?
    {
        info.sprintf("DIS Mode : On(0x02)/Off(0x03)/Hold(0x00) : %02X", g_RxBuf[2] );
        qDebug() << info;
        return 1;
    }
    else if (send_data == 0x02) // Version Information
    {
        info.sprintf("Vendor : 0x%02X%02X, Version : Model Code[0x%02X%02X], ROM[0x%02X%02X], Socket[0x%02X]",
            g_RxBuf[2], g_RxBuf[3], g_RxBuf[4], g_RxBuf[5], g_RxBuf[6], g_RxBuf[7], g_RxBuf[8]);
        qDebug() << info;
        //cnrk
        g_Camera_VenderID = (g_RxBuf[2]<<8) | (g_RxBuf[3]);

        emit sig_show_version(g_Camera_VenderID, g_RxBuf[6]<<8 | g_RxBuf[7]);
        return 1;
    }
    else if ( send_data == 0x37) // Model Information
    {
        info.sprintf("Model Code(Comlaser 1c) : [0x%02X%02X%02X], Version : [v%02X.%02X]",
            g_RxBuf[2], g_RxBuf[3], g_RxBuf[4], g_RxBuf[5], g_RxBuf[6]);
        qDebug() << info;
        return 1;
    }
    /* cnrk */
    else if (send_data == 0x50)
    {

        return 1;
    }
    return 0;
}


//------------------------------------------------------------------------------
//  Public : 수신된 패킷을 분석한 후 결과를 돌려준다.
//
//  [Return value]
//    1 : 하나의 패킷이 수신되었다.
//    0 : 하나의 패킷 수신이 완료되지 않았다.
//    전역변수 g_ReceiveData 에 현재 수신된 패킷 정보가 저장된다.
unsigned char ViscaPacket::ReceiveData( unsigned char RxData )
{
    unsigned char result=0;
    result =  CheckRcvMsg( RxData );
    if(result ==2)//inquires command
    {
        MsgDecoder();
    }
    return result;
}



void ViscaPacket::ParsingPacket()
{

}

