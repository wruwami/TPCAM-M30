#include "SerialLaserManager.h"

#include <QSerialPort>

#include "SerialPacket.h"

SerialLaserManager::SerialLaserManager()
{
    m_pSerial = new QSerialPort(this);
    laser_packet = new SerialPacket;

    laser_con = 0;
//    connectLaser();
    connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(serial_received()));
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
//                laser_packet->ParsingPacket(listview_laser, model_laser);
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
    if(m_pSerial->isOpen())
        m_pSerial->close();
    laser_con=0;
}

void SerialLaserManager::start_laser()
{
    unsigned char header=0xDA;//테스트 모드 설정
    unsigned char msg[2];
    unsigned char msgSize=1;
    msg[0]=0;//msg[0] x 10 = 1000[ms]

    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    if(m_pSerial)
        m_pSerial->write(data);

    header=0x99;//레이저 발사 요청
    msg[1];
    msgSize=0;
    msg[0]=0;
    data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);


    if(m_pSerial)
        m_pSerial->write(data);

}

void SerialLaserManager::request_distance()
{
    unsigned char header=0x59;//거리전송 요청
    unsigned char msg[1];
    unsigned char msgSize=1;
    msg[0]=1;
    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);


    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_speed_measure_mode(unsigned char mode)
{
    unsigned char header=0x3C;
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=mode;
    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::request_selftest()
{
    unsigned char header=0xD8;//selftest 요청
    unsigned char msg[1];
    unsigned char msgSize=0;
    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_weather_mode(unsigned char mode)
{
    unsigned char header=0xE2;//Set weather mode
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_AJamming_mode(unsigned char mode)
{
    unsigned char header=0x40;//Set Anti-Jamming mode
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_unit(unsigned char unit)
{
    unsigned char header=0x3B;//Set speed, distance Unit
    unsigned char msg[2];
    unsigned char msgSize=2;
    msg[0]=0x01;
    msg[1]=unit;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_buzzer_mode(unsigned char mode)
{
    unsigned char header=0xD6;//Set buzzer mode
    unsigned char msg[1];
    unsigned char msgSize=1;
    msg[0]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_detection_distance(double distance)
{
    unsigned char header=0x38;//Set dectection distance
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x01;
    msg[1]=(int)distance/256;
    msg[2]=(int)distance%256;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_detection_area(double area)
{
    unsigned char header=0x39;//Set dectection area
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x01;
    msg[1]=(int)area/256;
    msg[2]=(int)area%256;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::set_night_mode(unsigned char mode)
{
    unsigned char header=0xE9;//Set night mode
    unsigned char msg[1];
    unsigned char msgSize=1;
    msg[0]=mode;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::shutdown_laser()
{
    unsigned char header=0xEE;//shutdown laser board
    unsigned char msg[0];
    unsigned char msgSize=0;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::factoryreset_laser()
{
    unsigned char header=0xA5;//factory-reset laser board
    unsigned char msg[0];
    unsigned char msgSize=0;

    QByteArray data;

    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);
    if(m_pSerial)
        m_pSerial->write(data);
}




void SerialLaserManager::start_virtualSpeed()
{
    unsigned char header=0xDA;
    unsigned char msg[2];
    unsigned char msgSize=1;
    msg[0]=200;//msg[0] x 10 = 2000[ms]

    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    if(m_pSerial)
        m_pSerial->write(data);
}

void SerialLaserManager::show_laser_info()
{
    unsigned char header=0xE3;
    unsigned char msg[1];
    unsigned char msgSize=0;
    msg[0]=0;
    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);


    if(m_pSerial)
        m_pSerial->write(data);
}


void SerialLaserManager::stop_laser()
{
    unsigned char header=0x59;
    unsigned char msg[2];
    unsigned char msgSize=1;
    msg[0]=0;//msg[0] x 10 = 1000[ms]

    QByteArray data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);

    if(m_pSerial)
        m_pSerial->write(data);

    header=0x9A;
    msg[1];
    msgSize=0;
    msg[0]=0;
    data;
    if(laser_packet)
        data= laser_packet->MakePacket(header, msg, msgSize);


    if(m_pSerial)
        m_pSerial->write(data);
}

SerialPacket *SerialLaserManager::getLaser_packet() const
{
    return laser_packet;
}
