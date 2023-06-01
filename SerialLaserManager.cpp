#include "SerialLaserManager.h"

#include <QSerialPort>

#include "SerialPacket.h"

SerialLaserManager::SerialLaserManager()
{
    m_pSerial = new QSerialPort(this);
    laser_packet = new SerialPacket;

    laser_con = 0;
    connectLaser();
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

    if(laser_con==0)
    {
        if(!m_pSerial->open(QIODevice::ReadWrite)){
//            qDebug() << "Serial port open error";
        }
        else
        {
//             ui->pushButton_laser->setText("Disconnect");
             laser_con=1;
             return "Disconnect";
        }
    }
    else
    {
//        ui->pushButton_laser->setText("Connect");
        if(m_pSerial->isOpen())
            m_pSerial->close();
        laser_con=0;
        return "Connect";
    }
    return "";
}

void SerialLaserManager::close()
{
    if(m_pSerial->isOpen())
        m_pSerial->close();
    laser_con=0;
}
