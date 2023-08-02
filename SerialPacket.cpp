//------------------------------------------------------------------------------
//  Serial 송/수신 패킷 [Encode / Decode] 라이브러리
#include <stdio.h>
#include <string.h>
#include <QString>
#include <QDebug>
#include <QStandardItemModel>
#include "SerialPacket.h"


DistanceFormat distLaser;
_ST_LASER_PARAM		g_stLaserParam;

unsigned char	s_RxLength = 0;
unsigned char	s_RxBuf[MAX_PACKET_SIZE];

SerialPacket::SerialPacket(QObject *parent)
    : QObject{parent}
{
    Init();
}

SerialPacket::~SerialPacket()
{

}

void SerialPacket::Init()
{
	dleed=0;
	stxed =0;
	g_TxLength = 0;
	g_length = 0;
	g_RxLength = 0;
}
//------------------------------------------------------------------------------------
//	정상 유무에 상관없이, 하나의 패킷 수신이 완료되었는지 분석
//	[Return Value]
//		1 : 하나의 패킷 수신 완료
//		0 : 하나의 패킷이 완료되지 않음
//------------------------------------------------------------------------------------
unsigned char	SerialPacket::CheckRcvMsg(unsigned char RxData)
{
    static	unsigned char	s_DLEed = 0, s_STXed = 0;	// DLE, STX 수신여부 저장
    static	unsigned char	s_RcvLen = 0;	// 수신된 바이트 수
    unsigned char	IsPacket = 0;	// 패킷 수신 완료 여부

    /* 수신된 바이트 수가 최대 버퍼 크기를 초과하면, 중간에 패킷이 깨졌을 가능성이 농후함 */
    if(s_RcvLen >= MAX_PACKET_SIZE )
    {
        /* 모두 클리어 하고, 새롭게 수신 */
        s_STXed = s_DLEed = 0;
        s_RcvLen = s_RxLength = 0;
    }

    /* STX가 아미 수신된 상태 */
    if(s_STXed == 1)
    {
        if(s_DLEed == 1)	// 이전 데이터가 DLE였다면,
        {
            s_RxBuf[s_RcvLen++] = RxData;
            s_DLEed = 0;
        }
        else if(RxData == DLE)	// 이전 데이터가 DLE가 아닌 상태에서, DLE 데이터 수신
        {
            s_DLEed = 1;
        }
        else if(RxData == ETX)	// 이전 데이터가 DLE가 아닌 상태에서, ETX 수신
        {
            IsPacket = 1;
        }
        else
        {
            s_RxBuf[s_RcvLen++] = RxData;
        }
    }
    /* STX가 수신되지 않은 상태에서, 현재 수신된 데이터가 STX 라면 */
    else if(RxData == STX)
    {
        s_STXed = 1;
        s_DLEed = 0;
        s_RcvLen = s_RxLength = 0;
    }

    /* 하나의 패킷이 수신 완료된 경우, */
    if(IsPacket == 1)
    {
        s_STXed = s_DLEed = 0;
        s_RxLength = s_RcvLen;	// 패킷 제어 문자(STX, ETX, DLE)를 제외한 데이터 갯수
        return 1;
    }

    return 0;
}


//------------------------------------------------------------------------------------
//	수신된 하나의 패킷에 대하여 유효성 검사
//	[Return Value]
//		0 : 비정상 패킷
//		1 : 정상 패킷
//------------------------------------------------------------------------------------
unsigned char	SerialPacket::MsgDecoder()
{
    unsigned char	MsgLen, CheckSum, TestCheckSum, i;

    MsgLen		= s_RxBuf[0];				// 수신된 메세지 길이 정보
    CheckSum	= s_RxBuf[s_RxLength-1];	// 수신된 CheckSum

    /* 수신된 메세지 길이정보와 실제 수신 패킷의 길이가 일치하는지 체크 */
    /* 올바른 메세지 길이(MsgLen) = 전체 데이터 수 - 2  <== 여기에서 -2는 MsgLen, CheckSum 데이터를 제외하기 위함 */
    if( MsgLen != (s_RxLength - 2) )
    {
        return 0;
    }

    /* CheckSum 검사 */
    /* CheckSum = MsgLen부터 마지막 Msg까지의 합 결과의 LSB 8bit */
    TestCheckSum = 0x00;
    for(i=0 ; i<(s_RxLength-1) ; i++)
    {
        TestCheckSum += s_RxBuf[i];
    }
    if(CheckSum != TestCheckSum)
    {
        return 0;
    }

    /* 에러(유효성) 검사를 모두 통과하면, 실제 파싱된 데이터를 g_ReceiveData에 저장 */
    g_ReceiveData.Header		= s_RxBuf[1];	// Header
    g_ReceiveData.MsgLength	= MsgLen - 1;	// Header까지 제외한 실제 메세지(데이타)만의 길이
    for(i=0 ; i<g_ReceiveData.MsgLength ; i++)
    {
        g_ReceiveData.Msg[i] = s_RxBuf[i+2];
    }

    return 1;
}


//------------------------------------------------------------------------------
//  Public : 수신된 패킷을 분석한 후 결과를 돌려준다.
//
//  [Return value]
//    1 : 하나의 패킷이 수신되었다.
//    0 : 하나의 패킷 수신이 완료되지 않았다.
//    전역변수 g_ReceiveData 에 현재 수신된 패킷 정보가 저장된다.
//
signed char SerialPacket::ReceiveData( unsigned char RxData )
{
    //static  CString s_paketStr;
    if ( CheckRcvMsg( RxData )==1 )
    {
        if ( MsgDecoder()==1 )
        {
            //s_paketStr = "";
            return 1;
        }
    }
    return 0;
}




//------------------------------------------------------------------------------
//  Private : 제어문자와 동일한지 검사
//
//  [Return value]
//    1 : 데이터 d 가 제어문자와 동일하다.
//    0 : 데이터 d 가 제어문자와 다르다.
//
signed char SerialPacket::ChkControlText( unsigned char d )
{
    if ( (d == STX) || (d == DLE) || (d == ETX) )
        return 1;
    else
        return 0;
}

//------------------------------------------------------------------------------
//  Private : 송신 패킷의 형태로 인코딩
//
void SerialPacket::EncodePacket( unsigned char TotalMsgLen,
                                unsigned char Head,
                                unsigned char *Msg,
                                unsigned char Checksum,
                                 QByteArray *send)
{
    unsigned char i;

    // STX 삽입
    g_TxLength = 0;
    g_TxBuf[g_TxLength] = STX; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // MSGL 삽입
    if ( ChkControlText(TotalMsgLen) )
    {
        g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }
    g_TxBuf[g_TxLength] = TotalMsgLen; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // HEAD 삽입
    if ( ChkControlText(Head) )
    {
        g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }
    g_TxBuf[g_TxLength] = Head; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // Message 삽입
    for (i = 0; i < TotalMsgLen-1; i++)
    {
        if ( ChkControlText(Msg[i]) )
        {
            g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

        }
        g_TxBuf[g_TxLength] = Msg[i]; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }

    // Checksum 삽입
    if ( ChkControlText(Checksum) )
    {
        g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }
    g_TxBuf[g_TxLength] = Checksum; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // ETX 삽입
    g_TxBuf[g_TxLength] = ETX;
    send->push_back(g_TxBuf[g_TxLength]);
    g_TxLength++;


#ifdef SERIAL_DEBUG
    //pLog.SaveTexts("-----W------");
    for(int i=0; i<g_TxLength; i++)
    {
        //pLog.SaveTexts("%d\t %02x",i, g_TxBuf[i]);

    }
    //pLog.SaveTexts("-----W------");

#endif


}

//------------------------------------------------------------------------------
//  Public : 사용자가 새로운 송신할 패킷을 만든다.
//
QByteArray SerialPacket::MakePacket( unsigned char Head, unsigned char *Msg, unsigned char MsgSize )
{
    unsigned char i,
    TotalMsgLen,
    Checksum = 0x00;
    QByteArray send;
    send.clear();

    if ( MsgSize <= MAX_PACKET_DATA )
    {
        // MSGL을 구한다.
        TotalMsgLen = MsgSize + 1;//메세지의 개수 + 헤더개수

        // Checksum을 구한다.
        Checksum = TotalMsgLen + Head;
        for (i = 0; i < MsgSize; i++)
        {
            Checksum = (Checksum + Msg[i]) & 0xFF;
        }


        EncodePacket( TotalMsgLen,
            Head,
            Msg,
            Checksum,
            &send );

        return send;
    }
    return send;
}



//------------------------------------------------------------------------------
//  Public : ACK 패킷을 만든다.
//
void SerialPacket::AckPacket( void )
{
    unsigned char code = ACK;

    MakePacket( 0x01, &code, 1 );
}

//------------------------------------------------------------------------------
//  Public : NACK 패킷을 만든다.
//
void SerialPacket::NackPacket( void )
{
    unsigned char code = NACK;

    MakePacket( 0x01, &code, 1 );
}

void	cbRcvLaserParam(const unsigned char* pBuf, int Sel)
{
    if(Sel > 5)		return;

    switch(Sel)
    {
        case 0:	// cl_para 구조체
        {
            const unsigned char	sign		= pBuf[30];		// Sign of Offset
            const float		LD1_Offset_sign		=	(sign & 0x02)?-0.01:0.01;
            const float		LD2_Offset_sign		=	(sign & 0x10)?-0.01:0.01;

            g_stLaserParam.ModelNum		= pBuf[0];					// Model Number

            //if(g_hWnd)
            //	SendMessage(g_hWnd, WM_RCV_DEV_CLASS, (WPARAM)(g_stLaserParam.ModelNum), 0);

            g_stLaserParam.LimitSpd		= pBuf[6]*256 + pBuf[7];	// Limit Speed
            g_stLaserParam.DetectDist	= pBuf[8]*256 + pBuf[9];	// Detect Distance
            g_stLaserParam.Unit			= pBuf[15];					// Unit
            g_stLaserParam.PRF			= pBuf[31];					// PRF
            g_stLaserParam.LD1_Offset	= (pBuf[24]*256 + pBuf[25]) * LD1_Offset_sign;	// LD1 Distance Offset
            g_stLaserParam.LD2_Offset	= (pBuf[22]*256 + pBuf[23]) * LD2_Offset_sign;	// LD2 Distance Offset

            //g_RcvLaserParam		|=	0x01;
        }
        break;

        case 1:	// APD Volt
        {
            g_stLaserParam.APD1_Volt		= pBuf[0]*256 + pBuf[1];
            g_stLaserParam.APD1_DropStep	= pBuf[2];

            //g_RcvLaserParam		|=	0x02;
        }
        break;

        case 2:	// APD Drop Val
        {
            const int	APD1_Drop_Val_sign	= pBuf[1]?-1:1;
            g_stLaserParam.APD1_DropVal		= pBuf[0] * APD1_Drop_Val_sign;

            //g_RcvLaserParam		|=	0x04;
        }
        break;

        case 3:	// AD ref Volt
        {
            g_stLaserParam.AD_ref	= (pBuf[0]*256 + pBuf[1]) * 0.01;

            //g_RcvLaserParam		|=	0x08;
        }
        break;

        case 4:	// Blank
        {
            g_stLaserParam.Blank_C	= pBuf[1]*256 + pBuf[2];
            g_stLaserParam.Blank_F	= pBuf[3];

            //g_RcvLaserParam		|=	0x10;
        }
        break;

        case 5:	// Threshold
        {
            g_stLaserParam.Threshold	= pBuf[0];

            //g_RcvLaserParam		|=	0x20;
        }
        break;
    }
}


void SerialPacket::ParsingPacket()
{
//    g_RxLength = 0;
//    //pLog.SaveTexts("패킷의 Checksum과 계산한 Checksum이 다르다면-에러");
//    g_ReceiveData.Head =0;
//    g_ReceiveData.MsgLength=0;
//    memset(g_ReceiveData.Buffer, 0, sizeof(unsigned char)*MAX_PACKET_SIZE);

    switch(g_ReceiveData.Header)
    {
        case 0xDB:	// HEAD_SND_SPD	: 이미지 캡쳐 속도 수신
            {
                unsigned char	Unit;			// 속도 단위
                unsigned char	VehicleID;		// 차량 ID
                unsigned char	FrontView;		// 전면 인지 후면인지
                float			fSpeed, fDist;	// 속도와 검지된 거리

                Unit			= g_ReceiveData.Msg[0];
                VehicleID		= g_ReceiveData.Msg[1];
                FrontView		= g_ReceiveData.Msg[6];
                fSpeed			= float( (g_ReceiveData.Msg[2]<<8) | (g_ReceiveData.Msg[3]) ) * 0.010 * (FrontView==0?-1.0:1.0);
                fDist			= float( (g_ReceiveData.Msg[4]<<8) | (g_ReceiveData.Msg[5]) ) * (Unit==0?0.10:1.0);

                QString	strMsg;
                if(Unit == 0x00)	// Meter:km/h
                    strMsg.sprintf("%s SPD(%03d) : %.2fkm/h, %.1fm", g_ReceiveData.Header==0xDB?"--------->Capture":"RT", VehicleID, fSpeed, fDist);
                else	// Feet:MPH
                    strMsg.sprintf("%s SPD(%03d) : %.2fMPH, %.1fft", g_ReceiveData.Header==0xDB?"--------->Capture":"RT", VehicleID, fSpeed, fDist);

                qDebug() << strMsg;

                m_bIsCaptureOnDisplay = true;
                emit sig_showCaptureSpeedDistance(fSpeed, fDist, VehicleID);


            }break;
        case 0xDC:	// HEAD_SND_REALTIME_SPD : 실시간 속도 수신
            {
                unsigned char	Unit;			// 속도 단위
                unsigned char	VehicleID;		// 차량 ID
                unsigned char	FrontView;		// 전면 인지 후면인지
                float			fSpeed, fDist;	// 속도와 검지된 거리

                Unit			= g_ReceiveData.Msg[0];
                VehicleID		= g_ReceiveData.Msg[1];
                FrontView		= g_ReceiveData.Msg[6];
                fSpeed			= float( (g_ReceiveData.Msg[2]<<8) | (g_ReceiveData.Msg[3]) ) * 0.010 * (FrontView==0?-1.0:1.0);
                fDist			= float( (g_ReceiveData.Msg[4]<<8) | (g_ReceiveData.Msg[5]) ) * (Unit==0?0.10:1.0);

                QString	strMsg;
                if(Unit == 0x00)	// Meter:km/h
                    strMsg.sprintf("%s SPD(%03d) : %.2fkm/h, %.1fm", g_ReceiveData.Header==0xDB?"--------->Capture":"RT", VehicleID, fSpeed, fDist);
                else	// Feet:MPH
                    strMsg.sprintf("%s SPD(%03d) : %.2fMPH, %.1fft", g_ReceiveData.Header==0xDB?"--------->Capture":"RT", VehicleID, fSpeed, fDist);

                qDebug() << strMsg;

                if(!m_bIsCaptureOnDisplay)
                    emit sig_showSpeedDistance(fSpeed, fDist);

            }break;

        case 0x7C:	// 거리 정보 수신
            {
                unsigned int	uDist;		// 임시 거리
                float			fDist;		// 최종 거리 : 임시 거리 * 0.01
                unsigned char	uCfd, uLB;	// 레이저 수신 감도, 레이저 빔 번호
                unsigned char	uSeqNum;	// 시퀀스 상수(0, 1, 2, ....., 254, 255, 0, 1, ....)


                uDist	 = (g_ReceiveData.Msg[0]<<16) | (g_ReceiveData.Msg[1]<<8) | (g_ReceiveData.Msg[2]);
                if(g_stLaserParam.Unit==0)
                    fDist		 = uDist * 0.01;
                else
                    fDist		 = uDist * 0.1; //[ft]

                uCfd		 = g_ReceiveData.Msg[3];
                uSeqNum = g_ReceiveData.Msg[4];
                uLB		 = g_ReceiveData.Msg[5];


                QString str;
                str.sprintf("L%d_%.02fm(%dlv)", uLB, fDist, uCfd);
                qDebug() << str;

                if(!m_bIsCaptureOnDisplay)
                    emit sig_showDistance(fDist, uCfd);

            }
            break;

        case 0xD9:	// 셀프 테스트 결과 리턴
            {
                QString	strMsg;
                strMsg.sprintf("Result of Self Test = %s", g_ReceiveData.Msg[0]==0x01?"PASS":"FAIL");
            }break;

        case 0x57:		// 레이저 파라메타 수신
            {
                cbRcvLaserParam((unsigned char*)(g_ReceiveData.Msg), 0);
            }
            break;

        case 0x8C:		// APD Drop Val Response
            {
                cbRcvLaserParam((unsigned char*)(g_ReceiveData.Msg), 2);
            }
            break;

        case 0x76:		// APD Volt Response
            {
                cbRcvLaserParam((unsigned char*)(g_ReceiveData.Msg), 1);
            }
            break;

        case 0x4B:		// AD Ref Volt Response
            {
                cbRcvLaserParam((unsigned char*)(g_ReceiveData.Msg), 3);
            }
            break;

        case 0x7A:		// Blanking Response
            {
                cbRcvLaserParam((unsigned char*)(g_ReceiveData.Msg), 4);
            }
            break;

        case 0x63:		// Threshold Response
            {
                cbRcvLaserParam((unsigned char*)(g_ReceiveData.Msg), 5);
            }
            break;

        case 0xE5:	// 전원 정보 수신, BATT info
            {
                QString str;
                str.sprintf("Src.Info : SRC(%s), LEV(%d)"	, g_ReceiveData.Msg[0]==1? "BATT" : "EXT_DC", g_ReceiveData.Msg[1]);
                qDebug() << str;
            }
            break;

        case 0xEA:
            {
                QString msg;
                if(g_ReceiveData.Msg[0] & 0x01)
                    msg = ("[Temp]");
                if(g_ReceiveData.Msg[0] & 0x02)
                    msg += ("[LD]");
                if(g_ReceiveData.Msg[0] & 0x04)
                    msg += ("[APD]");
                if(g_ReceiveData.Msg[0] & 0x08)
                    msg += ("[LD Feedback]");

                msg = ("Err.Info : ") + msg;
                qDebug() << msg;
            }
            break;

        case 0xEC:		//  	디버그 정보 전송 (LCB → X2B)
            {
                short	tmp		=	(g_ReceiveData.Msg[1])*256 + (g_ReceiveData.Msg[2]) - 273;
                float	volt	=	((g_ReceiveData.Msg[3])*256 + (g_ReceiveData.Msg[4])) * 0.01;

                QString str;
                str.sprintf(("Debug.Info : ERR(0x%x), TEMP(%d), VOLT(%.02f)")
                                                    , g_ReceiveData.Msg[0], tmp, volt);

                qDebug() << str;
            }
            break;

        case 0xF0:			//  	메시지 헤더
            {
                  QString str;//, tstr;
                  str.sprintf("%s", g_ReceiveData.Msg);
                  qDebug() << str;

//                QString str, tstr;
//                str = g_ReceiveData.Msg;
//                tstr = str.Left(g_ReceiveData.MsgLength);

//                /* 레이저 정보 추출 */
//                CStringA t2str = str.Left(3);
//                int		Idx = 0;
//                char	szBuf[64]	= {0};
//                if(t2str == _T("Bui"))	// 빌드 날짜(0)
//                {
//                    Idx	= tstr.Find(":");
//                    qDebug() <<"%s", tstr.GetString()+Idx+2);
//                    memcpy(g_stLaserParam.BuildDate, tstr.GetString()+Idx+2, g_ReceiveData.MsgLength-(Idx+2));
//                }
//                else if(t2str == _T("Ver"))	// 버전(1)
//                {
//                    Idx	= tstr.Find(":");
//                    qDebug() <<"%s", tstr.GetString()+Idx+2);
//                    memcpy(g_stLaserParam.Ver, tstr.GetString()+Idx+2, g_ReceiveData.MsgLength-(Idx+2));
//                }
//                else if(t2str == _T("SN:")) // S/N(2)
//                {
//                    Idx	= tstr.Find(":");
//                    qDebug() <<"%s", tstr.GetString()+Idx+2);
//                    memcpy(g_stLaserParam.SN, tstr.GetString()+Idx+2, g_ReceiveData.MsgLength-(Idx+2));
//                }
//                else if(t2str == _T("PLD")) // PLD 버전(3)
//                {
//                    Idx	= tstr.Find(":");
//                    qDebug() <<"%s", tstr.GetString()+Idx+2);
//                    memcpy(g_stLaserParam.PLDVer, tstr.GetString()+Idx+1, g_ReceiveData.MsgLength-(Idx+1));
//                }
            }
            break;

        case 0xE4:
            {                 
                char	strBuf[31];
                QString disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 0, 30);
                disp.sprintf("Laser S/N : %s", strBuf);
                qDebug() << disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 30, 8);
                disp.sprintf("F/W version : %s", strBuf);
                emit sig_showVersion(QString(strBuf));
                qDebug() << disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 38, 11);
                disp.sprintf("F/W build date : %s", strBuf);
                qDebug() << disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 49, 5);
                disp.sprintf("PLD version : %s", strBuf);
                qDebug() << disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 54, 5);
                disp.sprintf("H/W version : %s", strBuf);

                disp.sprintf("Model Info :  %d", g_ReceiveData.Msg[59]);
                qDebug() << disp;

                disp.sprintf("PRF :  %d", g_ReceiveData.Msg[60]);
                qDebug() << disp;

                disp.sprintf("Unit :  %d", g_ReceiveData.Msg[61]);
                qDebug() << disp;

                disp.sprintf("Auto trigger :   %d", g_ReceiveData.Msg[62]);
                qDebug() << disp;

                disp.sprintf("CFD:   %d", g_ReceiveData.Msg[63]);
                qDebug() << disp;

                float dist_offset = (g_ReceiveData.Msg[64]?-1.0f:1.0f) * ( (g_ReceiveData.Msg[65]<<8) | g_ReceiveData.Msg[66]) * 0.01f;
                disp.sprintf("Dist offset :  %0.1f", dist_offset);
                qDebug() << disp;

                float speed_offset = (g_ReceiveData.Msg[67]?-1.0f:1.0f) * ( (g_ReceiveData.Msg[68]<<8) | g_ReceiveData.Msg[69]) * 0.01f;
                disp.sprintf("Speed offset :  %0.1f", speed_offset);
                qDebug() << disp;

                disp.sprintf("APD rated V : %dV", ((g_ReceiveData.Msg[70]<<8) | g_ReceiveData.Msg[71]));
                qDebug() << disp;

                disp.sprintf("APD drop step : %d", g_ReceiveData.Msg[72] );
                qDebug() << disp;

                disp.sprintf("APD drop value : %d", (signed char)g_ReceiveData.Msg[73] );
                qDebug() << disp;


                disp.sprintf("APD control : %d", g_ReceiveData.Msg[74] );
                qDebug() << disp;


                disp.sprintf("ADC ref V : %0.1f", ((g_ReceiveData.Msg[75]<<8) | g_ReceiveData.Msg[76]) * 0.01f);
                qDebug() << disp;


                disp.sprintf(" APD threshold : %d", g_ReceiveData.Msg[77] );
                qDebug() << disp;


                disp.sprintf("Private CFD level : %d", g_ReceiveData.Msg[78] );
                qDebug() << disp;


                disp.sprintf("Weather mode :  %d", g_ReceiveData.Msg[79] );
                qDebug() << disp;


                disp.sprintf("Blank coarse bit :  %d", g_ReceiveData.Msg[80] );
                qDebug() << disp;


                disp.sprintf("Anti-jamming :  %d", g_ReceiveData.Msg[81] );
                qDebug() << disp;


                disp.sprintf("Measurement mode :  %d", g_ReceiveData.Msg[82] );
                qDebug() << disp;


                disp.sprintf("Speed limit :  %d", ((g_ReceiveData.Msg[83]<<8) | g_ReceiveData.Msg[84]));
                qDebug() << disp;


                disp.sprintf("Detect distance :  %d", ((g_ReceiveData.Msg[85]<<8) | g_ReceiveData.Msg[86]));
                qDebug() << disp;


                disp.sprintf("Detect distance margin :  %d", ((g_ReceiveData.Msg[87]<<8) | g_ReceiveData.Msg[88]));
                qDebug() << disp;


                disp.sprintf("Night mode :  %d",g_ReceiveData.Msg[89]);
                qDebug() << disp;


            }break;

            /* TPCAM-H10 시리얼 출력 설정 */
        case 0xDE:
            {
                if(g_ReceiveData.Msg[0] == 0x02)
                {
                    qDebug() << "TPCAM H10 packet received";
                }
            }break;


        default:
            break;
    }
}

