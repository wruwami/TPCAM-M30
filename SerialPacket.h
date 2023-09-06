//------------------------------------------------------------------------------
//  Serial 송/수신 패킷 [Encode / Decode] 라이브러리
//  ComLASER SW
//
//#include "..\compiler.h"


#ifndef SerialPacketH
#define SerialPacketH

#include <QByteArray>
#include <QListView>
#include <QStandardItemModel>
#include <QObject>

//------------------------------------------------------------------------------
//  [Packet format]
//
//  STX         : Start of text
//  MSGL        : Message bytes + 1
//  HEAD        : 패킷의 헤더
//  Messahortge 0   : 메세지
//  Message 1   : 메세지
//    .         : 메세지
//    .         : 메세지
//  Message n   : 메세지
//  Checksum    : 패킷 제어문자 (STX, DLE, ETX)를 제외한 모든 바이트의 합
//  ETX         : End of text
//
//
//  DLE         : 데이터중 제어문자와 동일한 코드 앞에 삽입


#define MAX_PACKET_SIZE 			600          //패킷의 최대 버퍼
#define MAX_PACKET_DATA 			200          //패킷의 최대 바이트 크기

#define STX             			0x02        //패킷의 시작
#define ETX             			0x03        //패킷의 종료
#define DLE            		 		0x10        //패킷 제어문자 구분

#define ACK             			0x01        // ACK 패킷
#define NACK            			0xFF        // NACK 패킷

//------------------------------------------------------------------------------
// 제어부 요청 : HEAD_REQ
// 레이저 응답 : HEAD_RES
//
//버전정보
#define HEAD_REQ_VER    			0x60

//vs2 bottom point setting
#define HEAD_REQ_MOD    			0x62
#define HEAD_RES_MOD   				0x32

#define HEAD_RES_ALG   				0x33

//차종구분 카메라 트리거 높이 
#define HEAD_REQ_HEA    			0x64	//레이저에 셋팅
#define HEAD_RES_HEA   				0x34	//제어부로 전송

//일련번호
#define HEAD_REQ_ROM    			0x66 //요구, 셋팅
#define HEAD_RES_ROM    			0x36 //현재값 리턴

//교통 변수 관련 변수
#define HEAD_REQ_CAM    			0x67
#define HEAD_ACQ_CAM    			0x68
#define HEAD_RES_CAM    			0x37

//------------------------------------------------------------------------------
// 제어부 설정 : HEAD_SET
// 레이저 응답 : ACK/NACK
//
//APD 제어
#define HEAD_SET_ACT    			0x90


// 온도센서 셋팅 /전송
#define HEAD_SET_ALG    			0x92
#define HEAD_SET_LDV   	 			0x94 

//트리그 시작
#define HEAD_SET_TST   	 			0x99  

//트리그 종료
#define HEAD_SET_TED    			0x9A    

//------------------------------------------------------------------------------
// 2004. 2. 25일 추가패킷
#define HEAD_SET_LIN    			0xA4 // 

#define HEAD_SET_SAM    			0xA5 
#define HEAD_NSY_TRG   	 			0x53

#define HEAD_SET_LEV    			0xA6 //경계치(0레벨) 전압 가변 여부 

#define HEAD_SET_DEB    			0xA7 //거리 전송 8레벨 


//------------------------------------------------------------------------------
// 

#define HEAD_SET_RESET    			0xA1 //장비 S/W Reset
#define HEAD_BOOTLOADER    			0xA2 //fw update


//------------------------------------------------------------------------------
// 비동기 통신 (제어부 -> 레이저) : HEAD_NSY
//
//차종구분용 트리거
#define HEAD_NSY_DIS   				0x50 

//속도 및 거리 데이터 전송
#define HEAD_NSY_SPD   				0x51

//속도 및 거리 데이터 전송 (마일)
#define HEAD_MIL_SPD    			0x55


//------------------------------------------------------------------------------
// 2004. 11. 17일 추가패킷
#define HEAD_MESSAGE				0xF0	// 시리얼로 메세지를 전송할 경우
#define HEAD_COMMAND				0xF1	// 시리얼로 메세지를 입력받을 경우

//------------------------------------------------------------------------------
// vs2
// 2005. 04. 14일 추가패킷 
// HEAD_DN : pc -> vs
// HEAD_UP : vs -> pc
#define HEAD_DN_SET_ALGORITHM		0x54	// 시리얼로 알고리즘 시작/종료 
#define HEAD_DN_ACK_SETTING			0x55	// 시리얼로 알고리즘 현재 셋팅값 요청
#define HEAD_DN_SET_SETTING			0x56	// 시리얼로 알고리즘 현재 셋팅값 셋팅
#define HEAD_UP_GET_SETTING			0x57	// 시리얼로 알고리즘 현재 셋팅값 보내기
#define HEAD_UP_RESULT    			0x58	// 시리얼로 결과 값 전송
#define HEAD_DN_ACK_DISTANCE		0x59	// 시리얼로 거리 전송 시작/종료
#define HEAD_DN_ERROR_T   			0x5b	// 시리얼로 에러 문턱치 전송
#define HEAD_UP_ERROR_T   			0x5c	// 시리얼로 에러 문턱치 전송
#define HEAD_DN_ACK_ERROR_T			0x5d	// 시리얼로 에러 문턱치 요청 
#define HEAD_AB_MODE_SEL 			0x5E	//우천시 설정 변경...기/쓰기
#define HEAD_AB_MODE_SEL_SEND 		0x5F	//우천시 설정 전ㅇ송

#define HEAD_UP_CAMERA_TRIGGER		0x70	// 시리얼로 카메라 트리거 전송
#define HEAD_UN_SERIAL_BPS      	0x71	//시리얼 통신 속도 다운
#define HEAD_UP_SERIAL_OK       	0x72	//시리얼 통신연결 전송
#define HEAD_DN_SERIAL_OK       	0x73	//시리얼 통신연결
#define HEAD_UP_FAST_SPEED       	0x74	//[VS] fast speed
#define HEAD_FAST_SPD     			0x74	//[CL] FAST  속도 출력
#define HEAD_APD_VOLT_APPLY       	0x75	//APD 설정
#define HEAD_APD_VOLT_SEND       	0x76	//APD 설정 전송
#define HEAD_HW_BLANKING_APPLY      0x79	//블랭킹 설정
#define HEAD_HW_BLANKING_SEND      	0x7a	//블랭킹 설정 전송
#define HEAD_DISTANC_FLAG_SEND     	0x7b	//거리전송모드 선택
#define HEAD_UP_DISTANCE     		0x7c	//거리 전송
#define HEAD_LASER_POINTER_COMMAND	0x7f	// 레이저 포인터 on/off  
#define HEAD_LASER_POINTER_SEND		0x83	//	laser point on/off apply
#define HEAD_APD_VOLT_COMMAND		0x80	//	APD Volt
#define HEAD_OK_SIGNAL_COMMAND		0x81	//	Ok signal
#define HEAD_VEHICLE_STATE_SEND		0x86	//	차량의 시작과 끝을 알려준다.(binary 용)
#define HEAD_DN_CFD_ONOFF_SEND		0x8d	//	cfd on/off write
#define HEAD_DN_CLOOP_COMMAND		0x42	//  current loop trig
#define HEAD_DN_APD_TEMP_COMMAND	0x43	//APD temp sensor send
#define HEAD_VS_INPUT_FORMAT_SEND	0x4f	// input format(1- 바이너리, 2- 아스키)
#define HEAD_AD_REF_VOLT			0x88	//AD referance volt setting    
#define HEAD_AD_REF_VOLT_SEND		0x4b	// VS2 변수 읽기
#define HEAD_SIM_MODE    			0xA8 //
#define HEAD_APD_SEL				0x61
#define HEAD_APD_SEL_SEND			0x63
#define HEAD_AGING_REQUEST			0x89
#define HEAD_APD_AUTO_CAL			0x21	//APD Volt auto calibration

#define HEAD_FW_DOWNLOAD			0x30 	// Firmware download

//JAM
#define HEAD_JAM_REQ				0x40	//JAM PC-->CL
#define HEAD_JAM_SEND				0x41	//JAM CL-->PC 
#define HEAD_JAM_DETECT_SEND		0x69	//JAM DETECT CL-->PC 

#define HEAD_BUZ_ONOFF				0x4D	// 


#define HEAD_APDDROP_VOLT_REQUEST	0x8c	// APD  Drop 전압 read 
#define HEAD_APDDROP_VOLT_SEND		0x46	// APD  Drop 전압 write

#define HEAD_PRF_MUL_REQ			0x47	// PRF *  배수 read  PC-->CL
#define HEAD_PRF_MUL_SEND			0x48	// PRF *  배수 write  VS-->PC 

#define CFD_DECODE(x)		(((x >> 2) & 0x03) | ((x >> 3) & 0x1c))


struct MsgFormat
{
    unsigned char Header;
    unsigned char MsgLength;
    unsigned char Msg[MAX_PACKET_SIZE];
};

struct DistanceFormat
{
    unsigned int uDist; // ?? ??
    float fDist; // ?? ?? : ?? ?? * 0.01
    unsigned char uCfd, uLB; // ??? ?? ??, ??? ? ??
    unsigned char uSeqNum; // ??? ??(0, 1, 2, ....., 254, 255, 0, 1, ....)
};

typedef	struct	_ST_LASER_PARAM
{
    char	SN[31];
    char	Ver[10];
    char	BuildDate[15];
    char	PLDVer[10];
    int		ModelNum;
    int		PRF;
    int		DetectDist;
    int		LimitSpd;
    float	LD1_Offset;
    float	LD2_Offset;
    int		Unit;
    int		APD1_Volt;
    int		APD1_DropStep;
    int		APD1_DropVal;
    int		Blank_C;
    int		Blank_F;
    int		Threshold;
    float	AD_ref;
}_ST_LASER_PARAM;
extern _ST_LASER_PARAM		g_stLaserParam;

class SerialPacket : public QObject
{
    Q_OBJECT
public:
	unsigned char dleed, stxed;	//dle, stx 플레그
	unsigned char g_RxBuf[MAX_PACKET_SIZE];				//수신 데이터
	unsigned short  g_RxLength;				//수신데이터 길이
	struct MsgFormat g_ReceiveData;         //수신된 패킷을 분석 저장하는곳
	unsigned char g_TxBuf[MAX_PACKET_SIZE];				//송신할 패킷을 저장하는곳
	unsigned short g_TxLength;               //송신할 패킷의 길이를 저장
	unsigned char g_NPacketFlag;            //아스키 패킷 전송 플레그

	unsigned short g_length;

    //cnrk
//    bool m_bIsCaptureOnDisplay = false;

public:
    explicit SerialPacket(QObject *parent = nullptr);
    virtual ~SerialPacket();
    void	    Init();
    unsigned char CheckRcvMsg( unsigned char RxData );
    unsigned char MsgDecoder( void );
	signed char ChkControlText( unsigned char d );
	void EncodePacket( unsigned char TotalMsgLen,
					unsigned char Head,
					unsigned char *Msg,
                    unsigned char Checksum,
                        QByteArray *send);
	signed char ReceiveData( unsigned char RxData );
	signed char ProlaserReceiveData( unsigned char RxData );
    QByteArray MakePacket( unsigned char Head, unsigned char *Msg, unsigned char MsgSize );
	void AckPacket( void );
	void NackPacket( void );
	void SerialInformation(unsigned char info);
	signed char ReceiveData_D( unsigned char RxData );
    void ParsingPacket();

signals:
    void sig_showCaptureSpeedDistance(float fSpeed, float fDistance, int VehicleID);
    void sig_showSpeedDistance(float fSpeed, float fDistance);
    void sig_showDistance(float fDistance, int nSensitivity);
    void sig_showVersion(QString);
};


extern DistanceFormat distLaser;

#endif
