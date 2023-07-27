#include "SerialViscaManager.h"
#include <QSerialPort>
#include "ViscaPacket.h"

#include <QDebug>
#include <QEventLoop>

#include "ConfigManager.h"

SerialViscaManager::SerialViscaManager()
{
    serial_visca = new QSerialPort;
    visca_packet = new ViscaPacket;

    camera_con = 0;
    connectVisca();
    connect(serial_visca, SIGNAL(readyRead()), this, SLOT(receive_camera()));

    connect(m_pTimerInquiryZoom, SIGNAL(timeout()), this, SLOT(get_inquiry_zoom()));
    connect(m_pTimerInquiryFocus, SIGNAL(timeout()), this, SLOT(get_inquiry_focus()));
    connect(m_pTimerInquiryIris, SIGNAL(timeout()), this, SLOT(get_inquiry_iris()));
    connect(visca_packet, SIGNAL(sig_show_dzoom(QString)), this, SLOT(on_show_dzoom(QString)));
    connect(visca_packet, SIGNAL(sig_show_focus(QString)), this, SLOT(on_show_focus(QString)));
    this->show_dzoomPosition();
//    this->show_focusPosition();
}

SerialViscaManager::~SerialViscaManager()
{
    delete visca_packet;
    delete serial_visca;

    close();
}

QString SerialViscaManager::connectVisca()
{
    serial_visca->setPortName("ttyS0");
    serial_visca->setBaudRate(QSerialPort::Baud9600);
    serial_visca->setDataBits(QSerialPort::Data8);
    serial_visca->setParity(QSerialPort::NoParity);
    serial_visca->setStopBits(QSerialPort::OneStop);
    serial_visca->setFlowControl(QSerialPort::NoFlowControl);

    if(!serial_visca->open(QIODevice::ReadWrite)){
        return "Disconnect";//            qDebug() << "Serial port open error";
    }
    else
    {
        if (serial_visca->isOpen())
            return "Connect";
        else
            return "Disconnect";
    }
}

void SerialViscaManager::close()
{
    if(serial_visca->isOpen())
        serial_visca->close();
    camera_con=0;
}

ViscaPacket *SerialViscaManager::getVisca_packet() const
{
    return visca_packet;
}

void SerialViscaManager::receive_camera()
{
    qDebug() << "\r\n\r\n";
    QByteArray data= serial_visca->readAll();//readline-> readall
    if(data.size()>0)
    {
        qDebug() << "Camera Recive:" << data ;

        unsigned char byte_data;
        for(int i=0; i<data.size(); i++)
        {
            byte_data = data[i];

            if(visca_packet->ReceiveData(byte_data)==1)
            {
                //model->appendRow(new QStandardItem("Model?"));
                //ui->listView_3->setModel(model);

                //visca parsing
                visca_packet->ParsingPacket();
            }
        }

        data.clear();
    }
}


void SerialViscaManager::show_camera_version()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x00;
    msg[2]=0x02;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);

}


void SerialViscaManager::show_camera_model()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x00;
//    msg[2]=0x37;
    msg[2]=0x02;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);

}


void SerialViscaManager::set_infrared_mode_on()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x01;
    msg[3]=0x02;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_infrared_mode_off()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x01;
    msg[3]=0x03;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_infrared_mode_auto()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x51;
    msg[3]=0x02;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_noise_reduction_on(QString p)
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x53;
    msg[3]=0x00;
    QString dnr_value = p;

    int int_value = dnr_value.toInt();
    if(0<=int_value && int_value<=4 )
        msg[3]= msg[3] | int_value;
    else
    {
        msg[3]= 0x00;
        qDebug() << "over range";
    }

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_defog_off()
{
    unsigned char header=0x81;
    unsigned char msg[5];
    unsigned char msgSize=5;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x37;
    msg[3]=0x03;
    msg[4]=0x00;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_defog_on()
{
    unsigned char header=0x81;
    unsigned char msg[5];
    unsigned char msgSize=5;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x37;
    msg[3]=0x02;
    msg[4]=0x02;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

QString SerialViscaManager::change_defog_mode()
{
    static int toggle=0;
    unsigned char header=0x81;
    unsigned char msg[5];
    unsigned char msgSize=5;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x65;
    msg[3]=0x20;
    if(toggle==0)
    {
        toggle=1;
        msg[4]=0x01;
        qDebug() << "DEFOG Mode Auto";
    }
    else
    {
        toggle=0;
        msg[4]=0x00;
        qDebug() << "DEFOG Mode OFF";
    }

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);


    if(toggle==1)
    {
        return "DEFOG(Auto)";
    }
    else
    {
        return "DEFOG(OFF)";
    }
}

void SerialViscaManager::set_DIS_off()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x34;
    msg[3]=0x03;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_DIS_on()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x34;
    msg[3]=0x02;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_HLC_off()
{
    unsigned char header=0x81;
    unsigned char msg[5];
    unsigned char msgSize=5;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x14;
    msg[3]=0x00;
    msg[4]=0x00;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_HLC_on()
{
    unsigned char header=0x81;
    unsigned char msg[5];
    unsigned char msgSize=5;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x14;
    msg[3]=0x01;
    msg[4]=0x0A;

    QByteArray data;

    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::zoom(int currentIndex)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x47;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;
    int index = currentIndex;

    QString pqrs;
    if(g_Camera_VenderID == 0x0078)//KTNC
    {
        pqrs = g_Optical_Zoom_Value_KTNC[index];
    }
    else if(g_Camera_VenderID == 0x0020)//Wonwoo
    {
        pqrs = g_Optical_Zoom_Value_Wonwoo[index];
    }

    bool ok;
    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_zoom_pqrs = pqrs;

    //feedback
    m_pTimerInquiryZoom->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::plus_zoom()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x47;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;


    QString pqrs = m_zoom_pqrs;//g_Optical_Zoom_Value[index];
    qDebug() << "origin: "+ pqrs;

    bool ok;
    int int_pqrs = pqrs.toInt(&ok, 16) + 0x05;
    if(int_pqrs>0x4000)int_pqrs=0x4000;

    pqrs.sprintf("%x",int_pqrs);
    qDebug() << "add: "+ pqrs;


    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_zoom_pqrs = pqrs;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::minus_zoom()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x47;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;


    QString pqrs = m_zoom_pqrs;//g_Optical_Zoom_Value[index];
    qDebug() << "origin: "+ pqrs;

    bool ok;
    int int_pqrs = pqrs.toInt(&ok, 16) - 0x05;
    if(int_pqrs<0)int_pqrs=0;
    pqrs.sprintf("%x",int_pqrs);
    qDebug() << "add: "+ pqrs;


    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_zoom_pqrs = pqrs;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::zoom_from_pqrs(QString pqrs_input)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x47;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;

    QString pqrs = pqrs_input;


    bool ok;
    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_zoom_pqrs = pqrs;

    //feedback
    m_pTimerInquiryZoom->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::dzoom_from_pq(QString pq_input)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x46;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;

    QString pq = pq_input;

    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;
    msg[3]=0x00 ;
    msg[4]=0x00 ;
    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_Dzoom_pqrs = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::dzoom(int currentIndex)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x46;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;
    int index = currentIndex;

    QString pq;
    if(g_Camera_VenderID == 0x0078)//KTNC
    {
        pq = g_Digital_Zoom_Y_ASIX_KTNC[index];
    }
    else if(g_Camera_VenderID == 0x0020)//Wonwoo
    {
        pq = g_Digital_Zoom_Y_ASIX_Wonwoo[index];
    }

    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;
    msg[3]=0x00 ;
    msg[4]=0x00 ;
    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_Dzoom_pqrs = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::plus_dzoom()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x46;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;
    //int index = ui->comboBox_DZoom->currentIndex();

    QString pq = m_Dzoom_pqrs;//g_Digital_Zoom_Y_ASIX[index];
    bool ok;
    int int_pq = pq.toInt(&ok, 16) + 0x05;
    if(int_pq<0)int_pq=0;
    pq.sprintf("%x",int_pq);
    qDebug() << "add: "+ pq;

    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;
    msg[3]=0x00 ;
    msg[4]=0x00 ;
    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_Dzoom_pqrs = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::minus_dzoom()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x46;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;
    //int index = ui->comboBox_DZoom->currentIndex();

    QString pq = m_Dzoom_pqrs;//g_Digital_Zoom_Y_ASIX[index];
    bool ok;
    int int_pq = pq.toInt(&ok, 16) - 0x05;
    if(int_pq<0)int_pq=0;
    pq.sprintf("%x",int_pq);
    qDebug() << "add: "+ pq;

    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;
    msg[3]=0x00 ;
    msg[4]=0x00 ;
    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_Dzoom_pqrs = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_focus(QString a_pqrs)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x48;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;
    //int index = ui->comboBox_Zoom->currentIndex();

    QString pqrs = a_pqrs;// g_Optical_Zoom_Value[index];
    bool ok;
    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_focus_pqrs = pqrs;

    //feedback
    m_pTimerInquiryFocus->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);}

void SerialViscaManager::plus_focus()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x48;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;
    //int index = ui->comboBox_Zoom->currentIndex();

    QString pqrs = m_focus_pqrs;//ui->textEdit_Focus->toPlainText() ;// g_Optical_Zoom_Value[index];
    bool ok;
    int int_pqrs = pqrs.toInt(&ok, 16) + 0x05;
    if(int_pqrs<0)int_pqrs=0;
    pqrs.sprintf("%x",int_pqrs);
    qDebug() << "add: "+ pqrs;


    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_focus_pqrs = pqrs;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::minus_focus()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x48;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0,r=0,s=0;
    //int index = ui->comboBox_Zoom->currentIndex();

    QString pqrs = m_focus_pqrs;//ui->textEdit_Focus->toPlainText() ;// g_Optical_Zoom_Value[index];
    bool ok;
    int int_pqrs = pqrs.toInt(&ok, 16) - 0x05;
    if(int_pqrs<0)int_pqrs=0;
    pqrs.sprintf("%x",int_pqrs);
    qDebug() << "add: "+ pqrs;


    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_focus_pqrs = pqrs;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::separate_zoom_mode()
{
    //seperator mode
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x36;
    msg[3]=0x01;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::combine_zoom_mode()
{
    //seperator mode
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x36;
    msg[3]=0x00;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_manual_focus()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x38;
    msg[3]=0x03;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_auto_focus()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x38;
    msg[3]=0x02;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_AF_one_push_trigger()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x18;
    msg[3]=0x01;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_AE_shutter_priority()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x39;
    msg[3]=0x0A;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_AE_manual()
{
    //can set variable iris, gain, shutter
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x39;
    msg[3]=0x03;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::read_AE_mode()
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x39;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_shutter_speed(int currentIndex)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x4A;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;
    int index = currentIndex;

    QString pq;
    if(g_Camera_VenderID == 0x0078)//KTNC
    {
        pq =g_Shutter_Y_ASIX_KTNC[index] ;
    }
    else if(g_Camera_VenderID == 0x0020)//Wonwoo
    {
        pq =g_Shutter_Y_ASIX_Wonwoo[index] ;
    }
    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;

    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_shutter_pq = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_shutter_speed_from_pq(QString pq_input)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x4A;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;

    QString pq = pq_input;
    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;

    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_shutter_pq = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_gain(int currentIndex)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x4C;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;
    int index = currentIndex;

    QString pq;
    if(g_Camera_VenderID == 0x0078)//KTNC
    {
        pq =g_Gain_Y_ASIX_KTNC[index] ;
    }
    else if(g_Camera_VenderID == 0x0020)//Wonwoo
    {
        pq =g_Gain_Y_ASIX_Wonwoo[index] ;
    }
    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;

    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_gain_pq = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_gain_from_pq(QString pq_input)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x4C;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;

    QString pq = pq_input;
    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;

    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_gain_pq = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_iris(int currentIndex)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x4B;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;
    int index = currentIndex;

    QString pq;
    if(g_Camera_VenderID == 0x0078)//KTNC
    {
        pq =g_Iris_Y_ASIX_KTNC[index] ;
    }
    else if(g_Camera_VenderID == 0x0020)//Wonwoo
    {
        pq =g_Iris_Y_ASIX_Wonwoo[index] ;
    }
    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;

    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_iris_pq = pq;

    //feedback
    m_pTimerInquiryIris->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_iris_from_pq(QString pq_input)
{
    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=7;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x4B;
    msg[3]=0x00;
    msg[4]=0x00;
    msg[5]=0x00;
    msg[6]=0x00;
    int p=0,q=0;

    QString pq = pq_input;

    bool ok;
    p = pq.mid(0,1).toInt(&ok, 16);
    q = pq.mid(1,1).toInt(&ok, 16);

    qDebug() << pq;

    QString dd;
    dd.sprintf("P%X, Q%X", p,q);
    qDebug() << dd;

    msg[5]=0x00 | p;
    msg[6]=0x00 | q;

    m_iris_pq = pq;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::read_shutter_speed()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x4A;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::read_gain()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x4C;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_IRCorrection_standard()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x11;
    msg[3]=0x00;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::set_IRCorrection_IRlight()
{
    unsigned char header=0x81;
    unsigned char msg[4];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x11;
    msg[3]=0x01;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}


////inquiry
void SerialViscaManager::show_wideDynamicMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x3D;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_DISMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x34;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_IRCorrection()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x11;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_AFMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x57;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_ICR_OnOff()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x01;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_AutoICR()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x51;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_WBMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x35;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_AEMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x39;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_focusPosition()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x48;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_focusMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x38;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_zoomPosition()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x47;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_dzoomOnOff()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x06;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_dzoomPosition()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x46;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_dZoomMode()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x36;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::read_iris()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x4B;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::show_noiseReduction()
{
    unsigned char header=0x81;
    unsigned char msg[3];
    unsigned char msgSize=3;
    msg[0]=0x09;
    msg[1]=0x04;
    msg[2]=0x53;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    if(serial_visca)
        serial_visca->write(data);
}

void SerialViscaManager::get_inquiry_zoom()
{
    m_pTimerInquiryZoom->stop();
    QEventLoop loop;
    connect(visca_packet, SIGNAL(sig_show_zoom()), &loop, SLOT(quit()));
    show_zoomPosition();
    loop.exec();

    QString qstrgZoom_pqrs = QStringLiteral("%1").arg(visca_packet->m_qstrZoom_pqrs.toInt(nullptr, 16), 4, 16, QLatin1Char('0'));
    qstrgZoom_pqrs = qstrgZoom_pqrs.toUpper();

    QString qstrpqrs = m_zoom_pqrs;

    if(qstrpqrs == qstrgZoom_pqrs )
    {

    }
    else
    {
        emit sig_pb_zoom_clicked();
    }
}

void SerialViscaManager::get_inquiry_focus()
{
    m_pTimerInquiryFocus->stop();
    QEventLoop loop;
    connect(visca_packet, SIGNAL(sig_show_focus()), &loop, SLOT(quit()));
    show_focusPosition();
    loop.exec();

    QString qstrgFocus_pqrs = QStringLiteral("%1").arg(visca_packet->m_qstrFocus_pqrs.toInt(nullptr, 16), 4, 16, QLatin1Char('0'));

    QString qstrpqrs = m_focus_pqrs;

    qDebug() << qstrpqrs << ":" << qstrgFocus_pqrs;

    if(qstrpqrs == qstrgFocus_pqrs )
    {

    }
    else
    {
        emit sig_pb_focus_clicked();
    }
}

void SerialViscaManager::get_inquiry_iris()
{
    m_pTimerInquiryIris->stop();
    QEventLoop loop;
    connect(visca_packet, SIGNAL(sig_show_iris()), &loop, SLOT(quit()));
    read_iris();
    loop.exec();

    QString qstrgIris_pq = QStringLiteral("%1").arg(visca_packet->m_qstrIris_pq.toInt(nullptr, 16), 2, 16, QLatin1Char('0'));
    qstrgIris_pq = qstrgIris_pq.toUpper();

    QString qstrpq = m_iris_pq.mid(0, 2);

    qDebug() << qstrpq << ":" << qstrgIris_pq;

    if(qstrpq == qstrgIris_pq)
    {

    }
    else
    {
        emit sig_pb_iris_clicked();
    }
}

void SerialViscaManager::on_show_dzoom(QString zoom)
{
    m_Dzoom_pqrs = zoom;
}

void SerialViscaManager::on_show_focus(QString focus)
{
    m_focus_pqrs = focus;
}

void SerialViscaManager::SetDayMode(QJsonObject object)
{
    set_AE_shutter_priority();
    set_iris(object["Iris"].toInt());
    set_shutter_speed(object["Shutter"].toInt());
    set_gain(object["Gain"].toInt());
    set_noise_reduction_on(object["DNR"].toString());
    object["DIS"].toBool() ? set_DIS_on() : set_DIS_off();
    object["DEFOG"].toBool() ? set_defog_on() : set_defog_off();
    object["HLC"].toBool() ? set_HLC_on() : set_HLC_off();
}

void SerialViscaManager::SetDayMode(int index)
{
    ConfigManager config = ConfigManager("exposure.json");
    QJsonObject object = config.GetConfig();
    QJsonObject ret;
    switch (index) {
    case 1:
    {
        ret = object["Day"].toObject()["Dark"].toObject();
    }
        break;
    case 2:
    {
        ret = object["Day"].toObject()["Normal"].toObject();
    }
        break;
    case 3:
    {
        ret = object["Day"].toObject()["Bright"].toObject();
    }
        break;
    case 4:
    {
        ret = object["Night"].toObject()["Dark"].toObject();
    }
        break;
    case 5:
    {
        ret = object["Night"].toObject()["Normal"].toObject();
    }
        break;
    case 6:
    {
        ret = object["Night"].toObject()["Bright"].toObject();
    }
        break;
    }    
    set_AE_manual();
    set_iris(ret["Iris"].toInt());
    set_shutter_speed(ret["Shutter"].toInt());
    set_gain(ret["Gain"].toInt());
    set_noise_reduction_on(object["DNR"].toString());
    ret["DIS"].toBool() ? set_DIS_on() : set_DIS_off();
    ret["DEFOG"].toBool() ? set_defog_on() : set_defog_off();
    ret["HLC"].toBool() ? set_HLC_on() : set_HLC_off();
    set_AE_shutter_priority();
}
