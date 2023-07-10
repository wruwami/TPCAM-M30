//------------------------------------------------------------------------------
//  Serial ��/���� ��Ŷ [Encode / Decode] ���̺귯��
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


void SerialPacket::Init()
{
	dleed=0;
	stxed =0;
	g_TxLength = 0;
	g_length = 0;
	g_RxLength = 0;
}
//------------------------------------------------------------------------------------
//	���� ������ �������, �ϳ��� ��Ŷ ������ �Ϸ�Ǿ����� �м�
//	[Return Value]
//		1 : �ϳ��� ��Ŷ ���� �Ϸ�
//		0 : �ϳ��� ��Ŷ�� �Ϸ���� ����
//------------------------------------------------------------------------------------
unsigned char	SerialPacket::CheckRcvMsg(unsigned char RxData)
{
    static	unsigned char	s_DLEed = 0, s_STXed = 0;	// DLE, STX ���ſ��� ����
    static	unsigned char	s_RcvLen = 0;	// ���ŵ� ����Ʈ ��
    unsigned char	IsPacket = 0;	// ��Ŷ ���� �Ϸ� ����

    /* ���ŵ� ����Ʈ ���� �ִ� ���� ũ�⸦ �ʰ��ϸ�, �߰��� ��Ŷ�� ������ ���ɼ��� ������ */
    if(s_RcvLen >= MAX_PACKET_SIZE )
    {
        /* ��� Ŭ���� �ϰ�, ���Ӱ� ���� */
        s_STXed = s_DLEed = 0;
        s_RcvLen = s_RxLength = 0;
    }

    /* STX�� �ƹ� ���ŵ� ���� */
    if(s_STXed == 1)
    {
        if(s_DLEed == 1)	// ���� �����Ͱ� DLE���ٸ�,
        {
            s_RxBuf[s_RcvLen++] = RxData;
            s_DLEed = 0;
        }
        else if(RxData == DLE)	// ���� �����Ͱ� DLE�� �ƴ� ���¿���, DLE ������ ����
        {
            s_DLEed = 1;
        }
        else if(RxData == ETX)	// ���� �����Ͱ� DLE�� �ƴ� ���¿���, ETX ����
        {
            IsPacket = 1;
        }
        else
        {
            s_RxBuf[s_RcvLen++] = RxData;
        }
    }
    /* STX�� ���ŵ��� ���� ���¿���, ���� ���ŵ� �����Ͱ� STX ��� */
    else if(RxData == STX)
    {
        s_STXed = 1;
        s_DLEed = 0;
        s_RcvLen = s_RxLength = 0;
    }

    /* �ϳ��� ��Ŷ�� ���� �Ϸ�� ���, */
    if(IsPacket == 1)
    {
        s_STXed = s_DLEed = 0;
        s_RxLength = s_RcvLen;	// ��Ŷ ���� ����(STX, ETX, DLE)�� ������ ������ ����
        return 1;
    }

    return 0;
}


//------------------------------------------------------------------------------------
//	���ŵ� �ϳ��� ��Ŷ�� ���Ͽ� ��ȿ�� �˻�
//	[Return Value]
//		0 : ������ ��Ŷ
//		1 : ���� ��Ŷ
//------------------------------------------------------------------------------------
unsigned char	SerialPacket::MsgDecoder()
{
    unsigned char	MsgLen, CheckSum, TestCheckSum, i;

    MsgLen		= s_RxBuf[0];				// ���ŵ� �޼��� ���� ����
    CheckSum	= s_RxBuf[s_RxLength-1];	// ���ŵ� CheckSum

    /* ���ŵ� �޼��� ���������� ���� ���� ��Ŷ�� ���̰� ��ġ�ϴ��� üũ */
    /* �ùٸ� �޼��� ����(MsgLen) = ��ü ������ �� - 2  <== ���⿡�� -2�� MsgLen, CheckSum �����͸� �����ϱ� ���� */
    if( MsgLen != (s_RxLength - 2) )
    {
        return 0;
    }

    /* CheckSum �˻� */
    /* CheckSum = MsgLen���� ������ Msg������ �� ����� LSB 8bit */
    TestCheckSum = 0x00;
    for(i=0 ; i<(s_RxLength-1) ; i++)
    {
        TestCheckSum += s_RxBuf[i];
    }
    if(CheckSum != TestCheckSum)
    {
        return 0;
    }

    /* ����(��ȿ��) �˻縦 ��� ����ϸ�, ���� �Ľ̵� �����͸� g_ReceiveData�� ���� */
    g_ReceiveData.Header		= s_RxBuf[1];	// Header
    g_ReceiveData.MsgLength	= MsgLen - 1;	// Header���� ������ ���� �޼���(����Ÿ)���� ����
    for(i=0 ; i<g_ReceiveData.MsgLength ; i++)
    {
        g_ReceiveData.Msg[i] = s_RxBuf[i+2];
    }

    return 1;
}


//------------------------------------------------------------------------------
//  Public : ���ŵ� ��Ŷ�� �м��� �� ����� �����ش�.
//
//  [Return value]
//    1 : �ϳ��� ��Ŷ�� ���ŵǾ���.
//    0 : �ϳ��� ��Ŷ ������ �Ϸ���� �ʾҴ�.
//    �������� g_ReceiveData �� ���� ���ŵ� ��Ŷ ������ ����ȴ�.
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
//  Private : ����ڿ� �������� �˻�
//
//  [Return value]
//    1 : ������ d �� ����ڿ� �����ϴ�.
//    0 : ������ d �� ����ڿ� �ٸ���.
//
signed char SerialPacket::ChkControlText( unsigned char d )
{
    if ( (d == STX) || (d == DLE) || (d == ETX) )
        return 1;
    else
        return 0;
}

//------------------------------------------------------------------------------
//  Private : �۽� ��Ŷ�� ���·� ���ڵ�
//
void SerialPacket::EncodePacket( unsigned char TotalMsgLen,
                                unsigned char Head,
                                unsigned char *Msg,
                                unsigned char Checksum,
                                 QByteArray *send)
{
    unsigned char i;

    // STX ����
    g_TxLength = 0;
    g_TxBuf[g_TxLength] = STX; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // MSGL ����
    if ( ChkControlText(TotalMsgLen) )
    {
        g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }
    g_TxBuf[g_TxLength] = TotalMsgLen; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // HEAD ����
    if ( ChkControlText(Head) )
    {
        g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }
    g_TxBuf[g_TxLength] = Head; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // Message ����
    for (i = 0; i < TotalMsgLen-1; i++)
    {
        if ( ChkControlText(Msg[i]) )
        {
            g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

        }
        g_TxBuf[g_TxLength] = Msg[i]; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }

    // Checksum ����
    if ( ChkControlText(Checksum) )
    {
        g_TxBuf[g_TxLength] = DLE; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;

    }
    g_TxBuf[g_TxLength] = Checksum; send->push_back(g_TxBuf[g_TxLength]); g_TxLength++;


    // ETX ����
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
//  Public : ����ڰ� ���ο� �۽��� ��Ŷ�� �����.
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
        // MSGL�� ���Ѵ�.
        TotalMsgLen = MsgSize + 1;//�޼����� ���� + �������

        // Checksum�� ���Ѵ�.
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
//  Public : ACK ��Ŷ�� �����.
//
void SerialPacket::AckPacket( void )
{
    unsigned char code = ACK;

    MakePacket( 0x01, &code, 1 );
}

//------------------------------------------------------------------------------
//  Public : NACK ��Ŷ�� �����.
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
        case 0:	// cl_para ����ü
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


void SerialPacket::ParsingPacket(QListView *listView, QStandardItemModel *model)
{
//    g_RxLength = 0;
//    //pLog.SaveTexts("��Ŷ�� Checksum�� ����� Checksum�� �ٸ��ٸ�-����");
//    g_ReceiveData.Head =0;
//    g_ReceiveData.MsgLength=0;
//    memset(g_ReceiveData.Buffer, 0, sizeof(unsigned char)*MAX_PACKET_SIZE);

    switch(g_ReceiveData.Header)
    {
        case 0xDB:	// HEAD_SND_SPD	: �̹��� ĸ�� �ӵ� ����
            {
                unsigned char	Unit;			// �ӵ� ����
                unsigned char	VehicleID;		// ���� ID
                unsigned char	FrontView;		// ���� ���� �ĸ�����
                float			fSpeed, fDist;	// �ӵ��� ������ �Ÿ�

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
                model->appendRow(new QStandardItem(strMsg));

                m_bIsCaptureOnDisplay = true;
                emit sig_showCaptureSpeedDistance(fSpeed, fDist);


            }break;
        case 0xDC:	// HEAD_SND_REALTIME_SPD : �ǽð� �ӵ� ����
            {
                unsigned char	Unit;			// �ӵ� ����
                unsigned char	VehicleID;		// ���� ID
                unsigned char	FrontView;		// ���� ���� �ĸ�����
                float			fSpeed, fDist;	// �ӵ��� ������ �Ÿ�

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
                model->appendRow(new QStandardItem(strMsg));

                if(!m_bIsCaptureOnDisplay)
                    emit sig_showSpeedDistance(fSpeed, fDist);

            }break;

        case 0x7C:	// �Ÿ� ���� ����
            {
                unsigned int	uDist;		// �ӽ� �Ÿ�
                float			fDist;		// ���� �Ÿ� : �ӽ� �Ÿ� * 0.01
                unsigned char	uCfd, uLB;	// ������ ���� ����, ������ �� ��ȣ
                unsigned char	uSeqNum;	// ������ ���(0, 1, 2, ....., 254, 255, 0, 1, ....)


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
                model->appendRow(new QStandardItem(str));

                if(!m_bIsCaptureOnDisplay)
                    emit sig_showDistance(fDist, uCfd);

            }
            break;

        case 0xD9:	// ���� �׽�Ʈ ��� ����
            {
                QString	strMsg;
                strMsg.sprintf("Result of Self Test = %s", g_ReceiveData.Msg[0]==0x01?"PASS":"FAIL");
            }break;

        case 0x57:		// ������ �Ķ��Ÿ ����
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

        case 0xE5:	// ���� ���� ����, BATT info
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

        case 0xEC:		//  	����� ���� ���� (LCB �� X2B)
            {
                short	tmp		=	(g_ReceiveData.Msg[1])*256 + (g_ReceiveData.Msg[2]) - 273;
                float	volt	=	((g_ReceiveData.Msg[3])*256 + (g_ReceiveData.Msg[4])) * 0.01;

                QString str;
                str.sprintf(("Debug.Info : ERR(0x%x), TEMP(%d), VOLT(%.02f)")
                                                    , g_ReceiveData.Msg[0], tmp, volt);

                qDebug() << str;
            }
            break;

        case 0xF0:			//  	�޽��� ���
            {
                  QString str;//, tstr;
                  str.sprintf("%s", g_ReceiveData.Msg);
                  qDebug() << str;

//                QString str, tstr;
//                str = g_ReceiveData.Msg;
//                tstr = str.Left(g_ReceiveData.MsgLength);

//                /* ������ ���� ���� */
//                CStringA t2str = str.Left(3);
//                int		Idx = 0;
//                char	szBuf[64]	= {0};
//                if(t2str == _T("Bui"))	// ���� ��¥(0)
//                {
//                    Idx	= tstr.Find(":");
//                    qDebug() <<"%s", tstr.GetString()+Idx+2);
//                    memcpy(g_stLaserParam.BuildDate, tstr.GetString()+Idx+2, g_ReceiveData.MsgLength-(Idx+2));
//                }
//                else if(t2str == _T("Ver"))	// ����(1)
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
//                else if(t2str == _T("PLD")) // PLD ����(3)
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
                model->clear();
                QString disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 0, 30);
                disp.sprintf("Laser S/N : %s", strBuf);
                model->appendRow(new QStandardItem(disp));
                qDebug() << disp;

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 30, 8);
                disp.sprintf("F/W version : %s", strBuf);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 38, 11);
                disp.sprintf("F/W build date : %s", strBuf);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 49, 5);
                disp.sprintf("PLD version : %s", strBuf);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                memset(strBuf, 0, 31);	memcpy(strBuf, g_ReceiveData.Msg + 54, 5);
                disp.sprintf("H/W version : %s", strBuf);
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Model Info :  %d", g_ReceiveData.Msg[59]);
                qDebug() << disp;
                 model->appendRow(new QStandardItem(disp));

                disp.sprintf("PRF :  %d", g_ReceiveData.Msg[60]);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Unit :  %d", g_ReceiveData.Msg[61]);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Auto trigger :   %d", g_ReceiveData.Msg[62]);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("CFD:   %d", g_ReceiveData.Msg[63]);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                float dist_offset = (g_ReceiveData.Msg[64]?-1.0f:1.0f) * ( (g_ReceiveData.Msg[65]<<8) | g_ReceiveData.Msg[66]) * 0.01f;
                disp.sprintf("Dist offset :  %0.1f", dist_offset);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                float speed_offset = (g_ReceiveData.Msg[67]?-1.0f:1.0f) * ( (g_ReceiveData.Msg[68]<<8) | g_ReceiveData.Msg[69]) * 0.01f;
                disp.sprintf("Speed offset :  %0.1f", speed_offset);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("APD rated V : %dV", ((g_ReceiveData.Msg[70]<<8) | g_ReceiveData.Msg[71]));
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("APD drop step : %d", g_ReceiveData.Msg[72] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("APD drop value : %d", (signed char)g_ReceiveData.Msg[73] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("APD control : %d", g_ReceiveData.Msg[74] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("ADC ref V : %0.1f", ((g_ReceiveData.Msg[75]<<8) | g_ReceiveData.Msg[76]) * 0.01f);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf(" APD threshold : %d", g_ReceiveData.Msg[77] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Private CFD level : %d", g_ReceiveData.Msg[78] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Weather mode :  %d", g_ReceiveData.Msg[79] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Blank coarse bit :  %d", g_ReceiveData.Msg[80] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Anti-jamming :  %d", g_ReceiveData.Msg[81] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Measurement mode :  %d", g_ReceiveData.Msg[82] );
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Speed limit :  %d", ((g_ReceiveData.Msg[83]<<8) | g_ReceiveData.Msg[84]));
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Detect distance :  %d", ((g_ReceiveData.Msg[85]<<8) | g_ReceiveData.Msg[86]));
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Detect distance margin :  %d", ((g_ReceiveData.Msg[87]<<8) | g_ReceiveData.Msg[88]));
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));

                disp.sprintf("Night mode :  %d",g_ReceiveData.Msg[89]);
                qDebug() << disp;
                model->appendRow(new QStandardItem(disp));



                int rowCnt = model->rowCount();
                for(int i=0;i<rowCnt;i++)
                {
                    QBrush qBrush;
                    if(0 == (i % 2))
                    {
                        qBrush = QBrush(QColor(212, 244, 250, 255));
                        }
                    else {
                        qBrush = QBrush(QColor(246, 246, 246, 255));
                        }
                    model->setData(model->index(i, 0), qBrush, Qt::BackgroundColorRole);
                }
                listView->setModel(model);

            }break;

            /* TPCAM-H10 �ø��� ��� ���� */
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

