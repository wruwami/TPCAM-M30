//------------------------------------------------------------------------------
//  Serial ��/���� ��Ŷ [Encode / Decode] ���̺귯��
//  ComLASER SW
//
//#include "..\compiler.h"
#include <QByteArray>
#include <QListView>
#include <QStandardItemModel>

#ifndef SerialPacketH
#define SerialPacketH
//------------------------------------------------------------------------------
//  [Packet format]
//
//  STX         : Start of text
//  MSGL        : Message bytes + 1
//  HEAD        : ��Ŷ�� ���
//  Messahortge 0   : �޼���
//  Message 1   : �޼���
//    .         : �޼���
//    .         : �޼���
//  Message n   : �޼���
//  Checksum    : ��Ŷ ����� (STX, DLE, ETX)�� ������ ��� ����Ʈ�� ��
//  ETX         : End of text
//
//
//  DLE         : �������� ����ڿ� ������ �ڵ� �տ� ����


#define MAX_PACKET_SIZE 			600          //��Ŷ�� �ִ� ����
#define MAX_PACKET_DATA 			200          //��Ŷ�� �ִ� ����Ʈ ũ��

#define STX             			0x02        //��Ŷ�� ����
#define ETX             			0x03        //��Ŷ�� ����
#define DLE            		 		0x10        //��Ŷ ����� ����

#define ACK             			0x01        // ACK ��Ŷ
#define NACK            			0xFF        // NACK ��Ŷ

//------------------------------------------------------------------------------
// ����� ��û : HEAD_REQ
// ������ ���� : HEAD_RES
//
//��������
#define HEAD_REQ_VER    			0x60

//vs2 bottom point setting
#define HEAD_REQ_MOD    			0x62
#define HEAD_RES_MOD   				0x32

#define HEAD_RES_ALG   				0x33

//�������� ī�޶� Ʈ���� ���� 
#define HEAD_REQ_HEA    			0x64	//�������� ����
#define HEAD_RES_HEA   				0x34	//����η� ����

//�Ϸù�ȣ
#define HEAD_REQ_ROM    			0x66 //�䱸, ����
#define HEAD_RES_ROM    			0x36 //���簪 ����

//���� ���� ���� ����
#define HEAD_REQ_CAM    			0x67
#define HEAD_ACQ_CAM    			0x68
#define HEAD_RES_CAM    			0x37

//------------------------------------------------------------------------------
// ����� ���� : HEAD_SET
// ������ ���� : ACK/NACK
//
//APD ����
#define HEAD_SET_ACT    			0x90


// �µ����� ���� /����
#define HEAD_SET_ALG    			0x92
#define HEAD_SET_LDV   	 			0x94 

//Ʈ���� ����
#define HEAD_SET_TST   	 			0x99  

//Ʈ���� ����
#define HEAD_SET_TED    			0x9A    

//------------------------------------------------------------------------------
// 2004. 2. 25�� �߰���Ŷ
#define HEAD_SET_LIN    			0xA4 // 

#define HEAD_SET_SAM    			0xA5 
#define HEAD_NSY_TRG   	 			0x53

#define HEAD_SET_LEV    			0xA6 //���ġ(0����) ���� ���� ���� 

#define HEAD_SET_DEB    			0xA7 //�Ÿ� ���� 8���� 


//------------------------------------------------------------------------------
// 

#define HEAD_SET_RESET    			0xA1 //��� S/W Reset
#define HEAD_BOOTLOADER    			0xA2 //fw update


//------------------------------------------------------------------------------
// �񵿱� ��� (����� -> ������) : HEAD_NSY
//
//�������п� Ʈ����
#define HEAD_NSY_DIS   				0x50 

//�ӵ� �� �Ÿ� ������ ����
#define HEAD_NSY_SPD   				0x51

//�ӵ� �� �Ÿ� ������ ���� (����)
#define HEAD_MIL_SPD    			0x55


//------------------------------------------------------------------------------
// 2004. 11. 17�� �߰���Ŷ
#define HEAD_MESSAGE				0xF0	// �ø���� �޼����� ������ ���
#define HEAD_COMMAND				0xF1	// �ø���� �޼����� �Է¹��� ���

//------------------------------------------------------------------------------
// vs2
// 2005. 04. 14�� �߰���Ŷ 
// HEAD_DN : pc -> vs
// HEAD_UP : vs -> pc
#define HEAD_DN_SET_ALGORITHM		0x54	// �ø���� �˰��� ����/���� 
#define HEAD_DN_ACK_SETTING			0x55	// �ø���� �˰��� ���� ���ð� ��û
#define HEAD_DN_SET_SETTING			0x56	// �ø���� �˰��� ���� ���ð� ����
#define HEAD_UP_GET_SETTING			0x57	// �ø���� �˰��� ���� ���ð� ������
#define HEAD_UP_RESULT    			0x58	// �ø���� ��� �� ����
#define HEAD_DN_ACK_DISTANCE		0x59	// �ø���� �Ÿ� ���� ����/����
#define HEAD_DN_ERROR_T   			0x5b	// �ø���� ���� ����ġ ����
#define HEAD_UP_ERROR_T   			0x5c	// �ø���� ���� ����ġ ����
#define HEAD_DN_ACK_ERROR_T			0x5d	// �ø���� ���� ����ġ ��û 
#define HEAD_AB_MODE_SEL 			0x5E	//��õ�� ���� ����...����/����
#define HEAD_AB_MODE_SEL_SEND 		0x5F	//��õ�� ���� ������

#define HEAD_UP_CAMERA_TRIGGER		0x70	// �ø���� ī�޶� Ʈ���� ����
#define HEAD_UN_SERIAL_BPS      	0x71	//�ø��� ��� �ӵ� �ٿ�
#define HEAD_UP_SERIAL_OK       	0x72	//�ø��� ��ſ��� ����
#define HEAD_DN_SERIAL_OK       	0x73	//�ø��� ��ſ���
#define HEAD_UP_FAST_SPEED       	0x74	//[VS] fast speed
#define HEAD_FAST_SPD     			0x74	//[CL] FAST  �ӵ� ���
#define HEAD_APD_VOLT_APPLY       	0x75	//APD ����
#define HEAD_APD_VOLT_SEND       	0x76	//APD ���� ����
#define HEAD_HW_BLANKING_APPLY      0x79	//��ŷ ����
#define HEAD_HW_BLANKING_SEND      	0x7a	//��ŷ ���� ����
#define HEAD_DISTANC_FLAG_SEND     	0x7b	//�Ÿ����۸�� ����
#define HEAD_UP_DISTANCE     		0x7c	//�Ÿ� ����
#define HEAD_LASER_POINTER_COMMAND	0x7f	// ������ ������ on/off  
#define HEAD_LASER_POINTER_SEND		0x83	//	laser point on/off apply
#define HEAD_APD_VOLT_COMMAND		0x80	//	APD Volt
#define HEAD_OK_SIGNAL_COMMAND		0x81	//	Ok signal
#define HEAD_VEHICLE_STATE_SEND		0x86	//	������ ���۰� ���� �˷��ش�.(binary ��)
#define HEAD_DN_CFD_ONOFF_SEND		0x8d	//	cfd on/off write
#define HEAD_DN_CLOOP_COMMAND		0x42	//  current loop trig
#define HEAD_DN_APD_TEMP_COMMAND	0x43	//APD temp sensor send
#define HEAD_VS_INPUT_FORMAT_SEND	0x4f	// input format(1- ���̳ʸ�, 2- �ƽ�Ű)
#define HEAD_AD_REF_VOLT			0x88	//AD referance volt setting    
#define HEAD_AD_REF_VOLT_SEND		0x4b	// VS2 ���� �б�
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


#define HEAD_APDDROP_VOLT_REQUEST	0x8c	// APD  Drop ���� read 
#define HEAD_APDDROP_VOLT_SEND		0x46	// APD  Drop ���� write

#define HEAD_PRF_MUL_REQ			0x47	// PRF *  ��� read  PC-->CL
#define HEAD_PRF_MUL_SEND			0x48	// PRF *  ��� write  VS-->PC 

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
	unsigned char dleed, stxed;	//dle, stx �÷���
	unsigned char g_RxBuf[MAX_PACKET_SIZE];				//���� ������
	unsigned short  g_RxLength;				//���ŵ����� ����
	struct MsgFormat g_ReceiveData;         //���ŵ� ��Ŷ�� �м� �����ϴ°�
	unsigned char g_TxBuf[MAX_PACKET_SIZE];				//�۽��� ��Ŷ�� �����ϴ°�
	unsigned short g_TxLength;               //�۽��� ��Ŷ�� ���̸� ����
	unsigned char g_NPacketFlag;            //�ƽ�Ű ��Ŷ ���� �÷���

	unsigned short g_length;

    //cnrk
    bool m_bIsCaptureOnDisplay = false;

public:
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
    void ParsingPacket(QListView *listView, QStandardItemModel *model);

signals:
    void sig_showCaptureSpeedDistance(float fSpeed, float fDistance);
    void sig_showSpeedDistance(float fSpeed, float fDistance);
    void sig_showDistance(float fDistance, int nSensitivity);
};


extern DistanceFormat distLaser;

#endif
