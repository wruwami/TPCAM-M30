#include "SerialViscaManager.h"
#include <QSerialPort>
#include "ViscaPacket.h"

SerialViscaManager::SerialViscaManager()
{
    m_pSerial = new QSerialPort(this);
    visca_packet = new ViscaPacket;

    camera_con = 0;
    connectVisca();
    connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(receive_camera()));
}

QString SerialViscaManager::connectVisca()
{
    m_pSerial->setPortName("ttyS0");
    m_pSerial->setBaudRate(QSerialPort::Baud9600);
    m_pSerial->setDataBits(QSerialPort::Data8);
    m_pSerial->setParity(QSerialPort::NoParity);
    m_pSerial->setStopBits(QSerialPort::OneStop);
    m_pSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(camera_con==0)
    {
        if(!m_pSerial->open(QIODevice::ReadWrite)){
//            qDebug() << "Serial port open error";
        }
        else
        {
            if(camera_con==0) //바꿈
            {
//                ui->pushButton_visca->setText("Disconnect");
                camera_con=1;
                return "Disconnect";
            }
            else
            {
//                ui->pushButton_visca->setText("Connect");
                if(m_pSerial->isOpen())
                    m_pSerial->close();

                camera_con=0;
                return "Connect";
            }

        }
    }
    else
    {
//        ui->pushButton_visca->setText("Connect");
        if(m_pSerial->isOpen())
            m_pSerial->close();
        camera_con=0;
        return "Connect";
    }
}



void SerialViscaManager::receive_camera()
{

}

