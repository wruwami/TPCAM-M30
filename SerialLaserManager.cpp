
#include "SerialLaserManager.h"

#include <QSerialPort>

#include "SerialPacket.h"
#include "Logger.h"

SerialLaserManager::SerialLaserManager()
{
    m_pSerial = new QSerialPort;
    laser_packet = new SerialPacket;

    laser_con = 0;
    connectLaser();
    connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(serial_received()));

//    connect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), &hud, SLOT(showSpeedDistanceSensitivity(float, float)));
//    connect(laser_packet, SIGNAL(sig_showDistance(float,int)), &hud, SLOT(showDistanceSensitivity(float, int)));
//    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), &hud, SLOT(showCaptureSpeedDistance(float, float, int)));
//    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float, float, int)), this, SLOT(startCaptureSpeedTimer()));
    connect(m_pTimerCaptureSpeed, SIGNAL(timeout()), this, SLOT(set_IsCSOnDisplay_false()));

}

SerialLaserManager::~SerialLaserManager()
{
    close();
    delete m_pSerial;
    delete laser_packet;

}

void SerialLaserManager::serial_received()
{
//    qDebug() << "\r\n\r\n";
    QByteArray data= m_pSerial->readAll();//readLine->readAll
    if(data.size()>0)
    {
//        qDebug() << "Laser Recive:" << data ;

        unsigned char byte_data;
        for(int i=0; i<data.size(); i++)
        {
            byte_data = data[i];
            if(laser_packet->ReceiveData(byte_data)==1)
            {
                laser_packet->ParsingPacket();
//                listview_laser->scrollToBottom();
                //추가
//                hud.showSpeedDistance(laser_packet->m_nSpeed , laser_packet->m_fDistance);
//                hud.showSpeedDistanceSensitivity(laser_packet->m_nSpeed, laser_packet->m_fDistance, laser_packet->m_nSensitivity);
            }
        }
        data.clear();
    }
}

QString SerialLaserManager::connectLaser()
{
//    QString msg = __PRETTY_FUNCTION__;
    SetLogMsg(LASER_SEND_DATA, "connectLaser()");


    m_pSerial->setPortName("ttyS4");
    m_pSerial->setBaudRate(QSerialPort::Baud115200);
    m_pSerial->setDataBits(QSerialPort::Data8);
    m_pSerial->setParity(QSerialPort::NoParity);
    m_pSerial->setStopBits(QSerialPort::OneStop);
    m_pSerial->setFlowControl(QSerialPort::NoFlowControl);
//    qDebug() << "Serial";

    if(!m_pSerial->open(QIODevice::ReadWrite)){
        return "Disconnect";
    }
    else
    {
        if (m_pSerial->isOpen())
            return "Connect";
        else
            return "Disconnect";
    }
}

void SerialLaserManager::close()
{
    SetLogMsg(LASER_SEND_DATA, "close()");

    if(m_pSerial->isOpen())
        m_pSerial->close();
    laser_con=0;
}

void SerialLaserManager::start_laser()
{
    SetLogMsg(LASER_SEND_DATA, "start_laser()");

//    unsigned char header=0xDA;//테스트 모드 설정
//    unsigned char msg[2];
//    unsigned char msgSize=1;
//    msg[0]=0;//msg[0] x 10 = 1000[ms]

//    QByteArray data;
//    if(laser_packet)
//        data= laser_packet->MakePacket(header, msg, msgSize);

//    if(m_pSerial)
//        m_pSerial->write(data);

    unsigned char header=0x99;//레이저 발사 요청
    unsigned char msg[1];
    unsigned char msgSize=0;
    msg[0]=0;
    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
    try{
        m_pSerial->waitForBytesWritten(1000);
    }catch(...){
        SetLogMsg(LASER_SEND_DATA, "start_laser() sending bytes error");
    }

}

void SerialLaserManager::stop_virtualSpeed()
{
    SetLogMsg(LASER_SEND_DATA, "stop_virtualSpeed()");

    unsigned char header=0xDA;//테스트 모드 설정
    unsigned char msg[2];
    unsigned char msgSize=1;
    msg[0]=0;//msg[0] x 10 = 1000[ms]

    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::request_distance(bool bRequestOn)
{
    if (bRequestOn)
        SetLogMsg(LASER_SEND_DATA, "request_distance(true)");
    else
        SetLogMsg(LASER_SEND_DATA, "request_distance(false)");


    unsigned char header=0x59;//거리전송 요청
    unsigned char msg[1];
    unsigned char msgSize=1;

    if(bRequestOn)
        msg[0]=1;
    else
        msg[0]=0;

    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_speed_measure_mode(unsigned char mode)
{

    SetLogMsg(LASER_SEND_DATA, QString("set_speed_measure_mode(%1)").arg(mode));


    unsigned char header=0x3C;
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=mode;
    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::request_selftest()
{
    SetLogMsg(LASER_SEND_DATA, "request_selftest()");

    unsigned char header=0xD8;//selftest 요청
    unsigned char msg[1];
    unsigned char msgSize=0;
    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_weather_mode(unsigned char mode)
{
    SetLogMsg(LASER_SEND_DATA, QString("set_weather_mode(%1)").arg(mode));

    unsigned char header=0xE2;//Set weather mode
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_AJamming_mode(unsigned char mode)
{
    SetLogMsg(LASER_SEND_DATA, QString("set_AJamming_mode(%1)").arg(mode));

    unsigned char header=0x40;//Set Anti-Jamming mode
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_unit(unsigned char unit)
{
    SetLogMsg(LASER_SEND_DATA, QString("set_unit(%1)").arg(unit));

    unsigned char header=0x3B;//Set speed, distance Unit
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=unit;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_buzzer_mode(unsigned char mode)
{
    SetLogMsg(LASER_SEND_DATA, QString("set_buzzer_mode(%1)").arg(mode));

    unsigned char header=0x4E;//Set buzzer on/off(0=off, 1=on)
    unsigned char msg[1];
    unsigned char msgSize=1;
    msg[0]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_detection_distance(double distance)
{

    SetLogMsg(LASER_SEND_DATA, QString("set_detection_distance(%1)").arg(distance));

    unsigned char header=0x38;//Set dectection distance
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x01;
    msg[1]=(int)distance/256;
    msg[2]=(int)distance%256;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_detection_area(double area)
{
    SetLogMsg(LASER_SEND_DATA, QString("set_detection_area(%1)").arg(area));

    unsigned char header=0x39;//Set dectection area
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x01;
    msg[1]=(int)area/256;
    msg[2]=(int)area%256;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_night_mode(unsigned char mode)
{
    SetLogMsg(LASER_SEND_DATA, QString("set_night_mode(%1)").arg(mode));

    unsigned char header=0xE9;//Set night mode
    unsigned char msg[1];
    unsigned char msgSize=1;
    msg[0]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::shutdown_laser()
{
    SetLogMsg(LASER_SEND_DATA, "shutdown_laser()");

    unsigned char header=0xEE;//shutdown laser board
    unsigned char msg[0];
    unsigned char msgSize=0;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::factoryreset_laser()
{
    SetLogMsg(LASER_SEND_DATA, "factoryreset_laser()");

    unsigned char header=0xA5;//factory-reset laser board
    unsigned char msg[0];
    unsigned char msgSize=0;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}




void SerialLaserManager::start_virtualSpeed()
{
    SetLogMsg(LASER_SEND_DATA, "start_virtualSpeed()");

    unsigned char header=0xDA;
    unsigned char msg[2];
    unsigned char msgSize=1;
    msg[0]=200;//msg[0] x 10 = 2000[ms]

    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::show_laser_info()
{
    SetLogMsg(LASER_SEND_DATA, "show_laser_info()");

    unsigned char header=0xE3;
    unsigned char msg[1];
    unsigned char msgSize=0;
    msg[0]=0;
    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}


void SerialLaserManager::stop_laser()
{
//    QString log_msg = __PRETTY_FUNCTION__;
    SetLogMsg(LASER_SEND_DATA, "stop_laser()");

//    unsigned char header=0x59;
//    unsigned char msg[2];
//    unsigned char msgSize=1;
//    msg[0]=0;//msg[0] x 10 = 1000[ms]

//    QByteArray data;
//    if(laser_packet)
//        data= laser_packet->MakePacket(header, msg, msgSize);

//    if(m_pSerial)
//        m_pSerial->write(data);

    unsigned char header=0x9A;
    unsigned char msg[1];
    unsigned char msgSize=0;
    msg[0]=0;
    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    QMutexLocker locker(&m_writeMutex);
    if(m_pSerial)
        m_pSerial->write(data);
}

SerialPacket *SerialLaserManager::getLaser_packet()
{
    return laser_packet;
}

void SerialLaserManager::SetLaserDetectionAreaDistance(int zoom_index, bool UserModeOn)
{
    int distance = 0, area = 0;
    switch (zoom_index)
    {
    case 1:
    {
        if (UserModeOn)
        {
            distance = 20;
            area = 3;
        }
        else
        {
            distance = 18;
            area = 18;
        }
    }
        break;
    case 2:
    {
        if (UserModeOn)
        {
            distance = 40;
            area = 3;
        }
        else
        {
            distance = 48;
            area = 12;
        }

    }
        break;
    case 3:
    {
        if (UserModeOn)
        {
            distance = 60;
            area = 3;
        }
        else
        {
            distance = 80;
            area = 20;
        }

    }
        break;
    case 4:
    {
        if (UserModeOn)
        {
            distance = 80;
            area = 3;
        }
        else
        {
            distance = 130;
            area = 30;
        }

    }
        break;
    case 5:
    {
        if (UserModeOn)
        {
            distance = 100;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 6:
    {
        if (UserModeOn)
        {
            distance = 120;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 7:
    {
        if (UserModeOn)
        {
            distance = 140;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 8:
    {
        if (UserModeOn)
        {
            distance = 160;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 9:
    {
        if (UserModeOn)
        {
            distance = 180;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 10:
    {
        if (UserModeOn)
        {
            distance = 200;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    case 11:
    {
        if (UserModeOn)
        {
            distance = 220;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    case 12:
    {
        if (UserModeOn)
        {
            distance = 240;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    case 13:
    {
        if (UserModeOn)
        {
            distance = 260;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    }

    this->set_detection_distance(distance);
    this->set_detection_area(area);

}
