//------------------------------------------------------------------------------
//  Serial 송/수신 패킷 [Encode / Decode] 라이브러리
//  ComLASER SW

#include <QByteArray>
#include "SerialPacket.h"


#ifndef ViscaPacketH
#define ViscaPacketH

#define MAX_PACKET_BLOCK_DATA 17			//패킷의 최대 바이트 크기

//R:1
#define RECEVIE_ACK         0x41
#define COMPELETE_COMMAND   0x51
#define COMPELETE_INQUIRES  0x50
#define ERROR               0x61

struct Position
{
    unsigned char p;
    unsigned char q;
    unsigned char r;
    unsigned char s;
};

#define NUMBER_OPTICAL_ZOOM_CNT     30
#define NUMBER_DZOOM_CNT            12
#define NUMBER_IRIS_CNT             18
#define NUMBER_SHUTTER_CNT          22
#define NUMBER_GAIN_CNT_KTNC        16
#define NUMBER_GAIN_CNT_WONWOO      11

extern int g_Digital_Zoom_X_Asix_KTNC[];
extern QString g_Digital_Zoom_Y_ASIX_KTNC[];
extern QString g_Iris_Y_ASIX_KTNC[];
extern QString g_Shutter_Y_ASIX_KTNC[];
extern QString g_Shutter_X_ASIX_KTNC[];
extern QString g_Gain_Y_ASIX_KTNC[];
extern QString g_Optical_Zoom_Value_KTNC[];

extern int g_Digital_Zoom_X_Asix_Wonwoo[];
extern QString g_Digital_Zoom_Y_ASIX_Wonwoo[];
extern QString g_Iris_Y_ASIX_Wonwoo[];
extern QString g_Shutter_Y_ASIX_Wonwoo[];
extern QString g_Shutter_X_ASIX_Wonwoo[];
extern QString g_Gain_Y_ASIX_Wonwoo[];
extern QString g_Optical_Zoom_Value_Wonwoo[];

//cnrk
extern int g_Camera_VenderID;// = 0x0078;

class ViscaPacket : public QObject
{
    Q_OBJECT
public:
    unsigned char g_TxBuf[MAX_PACKET_SIZE];				//송신할 패킷을 저장하는곳
    unsigned short g_TxLength;               //송신할 패킷의 길이를 저장

    unsigned char g_RxBuf[MAX_PACKET_SIZE];				//수신 데이터
    unsigned short  g_RxLength;				//수신데이터 길이

    unsigned char send_data;

//    unsigned char g_RxBuf[MAX_PACKET_SIZE];
//    unsigned short  g_RxLength;
    
    int m_zoomPQRS;
    int m_focusPQRS;
    int m_gain;
    int m_shutter;
    int m_iris;
    int m_DZoom;

    QString m_qstrDZoom_pqrs;
    QString m_qstrZoom_pqrs;
    QString m_qstrFocus_pqrs;
    QString m_qstrShutter_pq;
    QString m_qstrIris_pq;


    Position g_ZoomPos;
    Position g_DZoomPos;
    Position g_FocusPos;
    Position g_ShutterPos;
    Position g_IrisPos;
    Position g_GainPos;
    Position g_BrightPos;
    unsigned char g_FocusMode;
    unsigned char g_DZoomOnOff;
    unsigned char g_DZoomMode;
    unsigned char g_WBMode;
    unsigned char g_AEMode;    
    unsigned char g_NRMode;

public:

    unsigned char CheckRcvMsg( unsigned char RxData );
    unsigned char MsgDecoder( );
    unsigned char ReceiveData( unsigned char RxData);
    void ParsingPacket();

    QByteArray BlockCamMakePacket( unsigned char Head, unsigned char *Msg, unsigned char MsgSize );
    void BlockCamEncodePacket(unsigned char TotalMsgLen,
                              unsigned char Head,
                              unsigned char *Msg,
                              QByteArray *send);

    //cnrk
    void initTable();
signals:
    void sig_show_zoom(QString);
    void sig_show_focus(QString);
    void sig_show_dzoom(QString);
    void sig_show_shutter();
    void sig_show_iris();
    void sig_show_version(int, int);
//    void sig_show
    void sig_show_gain(QString);
    void sig_show_shutter(QString);
    void sig_show_iris(QString);
    void sig_show_DNR(QString);
};



#endif
