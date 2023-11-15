#include "SerialViscaManager.h"
#include <QSerialPort>
#include <QThread>
#include <QtConcurrent>
#include "ViscaPacket.h"

#include <QDebug>
#include <QEventLoop>
#include <QJsonArray>

#include "ConfigManager.h"
#include "Logger.h"
#include "v4l2_thread.h"

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
//    connect(visca_packet, SIGNAL(sig_show_dzoom(QString)), this, SLOT(on_show_dzoom(QString)));
//    connect(visca_packet, SIGNAL(sig_show_focus(QString)), this, SLOT(on_show_focus(QString)));

//    connect(this, SIGNAL(sig_pb_zoom_clicked()), this, SLOT(on_pushButton_Zoom_clicked()));
//    connect(this, SIGNAL(sig_pb_focus_clicked(QString)), this, SLOT(on_pushButton_Focus_clicked(QString)));
//    connect(this, SIGNAL(sig_pb_shutter_clicked()), this, SLOT(on_pushButton_Shutter_clicked()));
//    connect(this, SIGNAL(sig_pb_iris_clicked()), this, SLOT(on_pushButton_Iris_clicked()));

    //OPT
     connect(m_pTimerCheckOPTdone, SIGNAL(timeout()), this, SLOT(check_OPT_done()));

    this->show_dzoomPosition();
//    this->show_focusPosition();
}

SerialViscaManager::~SerialViscaManager()
{
    close();

    delete m_pTimerInquiryZoom;
    delete m_pTimerInquiryFocus;
    delete m_pTimerInquiryIris;
    delete m_pTimerCheckOPTdone;

    delete visca_packet;
    delete serial_visca;
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
//    qDebug() << "\r\n\r\n";
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
    SetLogMsg(VISCA_SEND_DATA, "show_camera_version()");
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }

}


void SerialViscaManager::show_camera_model()
{
    SetLogMsg(VISCA_SEND_DATA, "show_camera_model()");
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }

}


void SerialViscaManager::set_infrared_mode_on()
{
    SetLogMsg(VISCA_SEND_DATA, "set_infrared_mode_on()");
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_infrared_mode_off()
{
    SetLogMsg(VISCA_SEND_DATA, "set_infrared_mode_off()");
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_infrared_mode_auto()
{
    SetLogMsg(VISCA_SEND_DATA, "set_infrared_mode_auto()");
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_defog_off()
{
    SetLogMsg(VISCA_SEND_DATA, "set_defog_off()");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_defog_on()
{
    SetLogMsg(VISCA_SEND_DATA, "set_defog_on()");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }


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
    SetLogMsg(VISCA_SEND_DATA, "set_dis_off()");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_DIS_on()
{
    SetLogMsg(VISCA_SEND_DATA, "set_dis_on()");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_HLC_off()
{
    SetLogMsg(VISCA_SEND_DATA, "set_hlc_off()");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_HLC_on()
{
    SetLogMsg(VISCA_SEND_DATA, "set_hlc_on()");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::zoom(int currentIndex)
{
    SetLogMsg(VISCA_SEND_DATA, QString("zoom(%1)").arg(currentIndex));

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

    zoom_count = 0;

    //feedback
    m_pTimerInquiryZoom->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::plus_zoom()
{
    SetLogMsg(VISCA_SEND_DATA, "plus_zoom");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::minus_zoom()
{
    SetLogMsg(VISCA_SEND_DATA, "minus_zoom");

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::zoom_from_pqrs(QString pqrs_input)
{
    SetLogMsg(VISCA_SEND_DATA, QString("zoom_from_pqrs(%1)").arg(pqrs_input));

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
//    qDebug() << pqrs;

    QString dd;
    dd.sprintf("set zoom P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_zoom_pqrs = pqrs;

    zoom_count = 0;

    //feedback
    m_pTimerInquiryZoom->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::zoom_from_pqrs_noFeedback(QString pqrs_input)
{
    SetLogMsg(VISCA_SEND_DATA, QString("zoom_from_pqrs_noFeedback(%1)").arg(pqrs_input));

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
//    qDebug() << pqrs;

    QString dd;
    dd.sprintf("set zoom P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_zoom_pqrs = pqrs;

    zoom_count = 0;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::dzoom_from_pq(QString pq_input)
{
    SetLogMsg(VISCA_SEND_DATA, QString("dzooom_from_pq(%1").arg(pq_input));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::dzoom(int currentIndex)
{
    SetLogMsg(VISCA_SEND_DATA, QString("dzoom(%1").arg(currentIndex));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::plus_dzoom()
{
    SetLogMsg(VISCA_SEND_DATA, "plus_dzoom");

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
    if(int_pq>0xEB) int_pq=0xEB;
    //    pq.sprintf("%x",int_pq);
    pq = QString("%1").arg(int_pq, 2, 16, QChar('0'));
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::minus_dzoom()
{
    SetLogMsg(VISCA_SEND_DATA, " minus_dzoom");

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
    //    pq.sprintf("%x",int_pq);
    pq = QString("%1").arg(int_pq, 2, 16, QChar('0'));
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}
void SerialViscaManager::set_focus(QString a_pqrs)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_focus(%1)").arg(a_pqrs));

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
    int int_pqrs = a_pqrs.toInt(nullptr, 16);
    if(int_pqrs<100)
    {
        int_pqrs=0x0100;
    }
    else if(int_pqrs>0xFF00)
    {
        int_pqrs=0xFF00;
    }
    QString pqrs = QString("%1").arg(int_pqrs, 4, 16, QChar('0'));
//    QString pqrs = a_pqrs;// g_Optical_Zoom_Value[index];
    bool ok;
    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    SetLogMsg(VISCA_SEND_DATA, QString("set_focus("+ pqrs + ")2"));

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_focus_pqrs = pqrs;

    focus_count = 0;


    //feedback
    m_pTimerInquiryFocus->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}
void SerialViscaManager::set_focus_noFeedback(QString a_pqrs)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_focus_noFeedback(%1)").arg(a_pqrs));

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
    int int_pqrs = a_pqrs.toInt(nullptr, 16);
    if(int_pqrs<100)
    {
        int_pqrs=0x0100;
    }
    else if(int_pqrs>0xFF00)
    {
        int_pqrs=0xFF00;
    }
    QString pqrs = QString("%1").arg(int_pqrs, 4, 16, QChar('0'));
//    QString pqrs = a_pqrs;// g_Optical_Zoom_Value[index];
    bool ok;
    p = pqrs.mid(0,1).toInt(&ok, 16);
    q = pqrs.mid(1,1).toInt(&ok, 16);
    r = pqrs.mid(2,1).toInt(&ok, 16);
    s = pqrs.mid(3,1).toInt(&ok, 16);
    qDebug() << pqrs;

    SetLogMsg(VISCA_SEND_DATA, QString("set_focus("+ pqrs + ")2"));

    QString dd;
    dd.sprintf("P%X, Q%X, R%X, S%X", p,q,r,s);
    qDebug() << dd;
    msg[3]=0x00 | p;
    msg[4]=0x00 | q;
    msg[5]=0x00 | r;
    msg[6]=0x00 | s;

    m_focus_pqrs = pqrs;

    focus_count = 0;

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}
void SerialViscaManager::plus_focus()
{
    SetLogMsg(VISCA_SEND_DATA, "plus_focus");

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
    int int_pqrs = pqrs.toInt(&ok, 16) + 0x100;
    if(int_pqrs<100)
    {
        int_pqrs=0x0100;
    }
    else if(int_pqrs>0xFF00)
    {
        int_pqrs=0xFF00;
    }
    pqrs = QString("%1").arg(int_pqrs, 4, 16, QChar('0'));

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

    //feedback
     m_pTimerInquiryFocus->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::minus_focus()
{
    SetLogMsg(VISCA_SEND_DATA, "minus_focus");

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
    int int_pqrs = pqrs.toInt(&ok, 16) - 0x100;
    if(int_pqrs<100)
    {
        int_pqrs=0x0100;
    }
    else if(int_pqrs>0xFF00)
    {
        int_pqrs=0xFF00;
    }
    pqrs = QString("%1").arg(int_pqrs, 4, 16, QChar('0'));

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

    //feedback
     m_pTimerInquiryFocus->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::separate_zoom_mode()
{
    SetLogMsg(VISCA_SEND_DATA, QString("separate_zoom_mode"));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_manual_focus()
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_manual_focus"));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_AF_one_push_trigger()
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_AF_one_push_trigger"));

    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x18;
    msg[3]=0x01;

    opt_count = 0;

    m_pTimerCheckOPTdone->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_AE_shutter_priority()
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_AE_shutter_priority"));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_AE_manual()
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_AE_manual"));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_AE_Mode(QString p)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_AE_Mode(%1)").arg(p));

    unsigned char header=0x81;
    unsigned char msg[10];
    unsigned char msgSize=4;
    msg[0]=0x01;
    msg[1]=0x04;
    msg[2]=0x39;
    msg[3]=p.toInt(nullptr, 16);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_shutter_speed(int currentIndex)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_shuuter_spped(%1)").arg(currentIndex));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_shutter_speed_from_pq(QString pq_input)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_shuuter_spped_from_pq(%1)").arg(pq_input));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_gain(int currentIndex)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_gain(%1)").arg(currentIndex));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_gain_from_pq(QString pq_input)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_gain_from_pq(%1)").arg(pq_input));

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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_iris(int currentIndex)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_iris(%1)").arg(currentIndex));

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

    iris_count = 0;

    //feedback
    m_pTimerInquiryIris->start(500);

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::set_iris_from_pq(QString pq_input,  bool isAutoIris)
{
    SetLogMsg(VISCA_SEND_DATA, QString("set_iris_from_pq(%1)%2").arg(pq_input).arg(isAutoIris));

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

    if(isAutoIris)
    {

    }else{
        iris_count = 0;
    //feedback
    m_pTimerInquiryIris->start(20);
    }

    QByteArray data;
    if(visca_packet)
        data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

    qDebug() << data;

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
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

    QMutexLocker locker(&m_writeMutex);
    if(serial_visca)
        {serial_visca->write(data); serial_visca->waitForBytesWritten(m_waitTimeout); QThread::msleep(40); }
}

void SerialViscaManager::get_inquiry_zoom()
{
//    m_pTimerInquiryZoom->stop();
    QEventLoop loop;
    connect(visca_packet, SIGNAL(sig_show_zoom(QString)), &loop, SLOT(quit()));
    show_zoomPosition();
    loop.exec();

    QString qstrgZoom_pqrs = QStringLiteral("%1").arg(visca_packet->m_qstrZoom_pqrs.toInt(nullptr, 16), 4, 16, QLatin1Char('0'));
    qstrgZoom_pqrs = qstrgZoom_pqrs.toUpper();

    QString qstrpqrs = m_zoom_pqrs;

    if(qstrpqrs == qstrgZoom_pqrs )
    {
        zoom_count++;
        if(zoom_count >= CHECK_OPT_DONE_COUNTER)
        {
            m_pTimerInquiryZoom->stop();

        }
    } else {
        zoom_from_pqrs(qstrpqrs);
        zoom_count = 0;
    }
}

void SerialViscaManager::get_inquiry_focus()
{
//    m_pTimerInquiryFocus->stop();
    QEventLoop loop;
    connect(visca_packet, SIGNAL(sig_show_focus(QString)), &loop, SLOT(quit()));
    show_focusPosition();
    loop.exec();

    QString qstrgFocus_pqrs = QStringLiteral("%1").arg(visca_packet->m_qstrFocus_pqrs.toInt(nullptr, 16), 4, 16, QLatin1Char('0'));

    QString qstrpqrs = m_focus_pqrs;

//    qDebug() << qstrpqrs << ":" << qstrgFocus_pqrs;

    if(qstrpqrs == qstrgFocus_pqrs)
    {
        focus_count++;
        if(focus_count >= CHECK_OPT_DONE_COUNTER)
        {
            m_pTimerInquiryFocus->stop();
        }
    }
    else
    {
        set_focus(m_focus_pqrs);
        focus_count = 0;
    }

}

void SerialViscaManager::get_inquiry_iris()
{
//    m_pTimerInquiryIris->stop();
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
        iris_count++;
        if(iris_count >= CHECK_OPT_DONE_COUNTER)
        {
            m_pTimerInquiryIris->stop();
        }
    }
    else
    {
        bool isAutoIris = false;
        int dnn = ConfigManager("parameter_setting2.json").GetConfig()["day&night selection"].toInt();
        if (dnn >= 0 && dnn < 4)
            isAutoIris = true;
        set_iris_from_pq(qstrpq, isAutoIris);
        iris_count = 0;
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

void SerialViscaManager::SetDayMode(QJsonObject object, bool bDay, bool bFocus)
{
    set_AE_Mode("03");
    set_iris_from_pq(object["Iris"].toString(), bDay);
    set_shutter_speed_from_pq(object["Shutter"].toString());
    set_gain_from_pq(object["Gain"].toString());
    set_AE_Mode(object["Priority"].toString());
    set_noise_reduction_on(object["DNR"].toString());
    object["DIS"].toBool() ? set_DIS_on() : set_DIS_off();
    object["DEFOG"].toBool() ? set_defog_on() : set_defog_off();
    object["HLC"].toBool() ? set_HLC_on() : set_HLC_off();

    if (bDay)
    {
        set_infrared_mode_off();
        v4l2_thread::getInstance()->setUseFlash(false);
    }
    else
    {
        set_infrared_mode_on();
        v4l2_thread::getInstance()->setUseFlash(true);
    }

    if (bFocus)
    {
        ConfigManager config3 = ConfigManager("parameter_enforcement.json");
        QJsonObject object3 = config3.GetConfig();

        int zoom_index = object3["zoom index"].toInt() - 1;
        SetFocus(zoom_index);
    }

//    show_ICR_OnOff();
//    object.keys()
//    if (object > 0 && index < 4)
//        set_infrared_mode_off();
//    else
//        set_infrared_mode_on();
}

void SerialViscaManager::SetFocus(int index)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();

    object = ConfigManager("parameter_setting2.json").GetConfig();
    int daynight = object["day&night selection"].toInt();
    object = ConfigManager("focus.json").GetConfig();
    QJsonArray ar;
    if (daynight > 0 && daynight < 4)
    {
        if (userMode == 1)
        {
            ar = object["st day focus"].toArray();
            this->set_focus(ar[index].toString());
        }
        else
        {
            ar = object["lt day focus"].toArray();
            this->set_focus(ar[index].toString());
        }
    }
    else
    {
        if (userMode == 1)
        {
            ar = object["st night focus"].toArray();
            this->set_focus(ar[index].toString());
        }
        else
        {
            ar = object["lt night focus"].toArray();
            this->set_focus(ar[index].toString());
        }
    }
}

void SerialViscaManager::SetFocusForZoomFocus(int index, int ndaynight)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();

    int daynight = ndaynight;
    object = ConfigManager("focus.json").GetConfig();
    QJsonArray ar;
    if (daynight > 0 && daynight < 4)
    {
        ar = object["lt day focus"].toArray();
        this->set_focus(ar[index].toString());
    }
    else
    {
        ar = object["lt night focus"].toArray();
        this->set_focus(ar[index].toString());
    }
}

void SerialViscaManager::SetFocusForVmode(int index, int ndaynight)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();

    int daynight = ndaynight;
    object = ConfigManager("focus.json").GetConfig();
    QJsonArray ar;
    if (daynight > 0 && daynight < 4)
    {
        ar = object["lt day focus"].toArray();
        this->set_focus_noFeedback(ar[index].toString());
    }
    else
    {
        ar = object["lt night focus"].toArray();
        this->set_focus_noFeedback(ar[index].toString());
    }
}

void SerialViscaManager::SetZoom(int index)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();
    object = ConfigManager("zoom.json").GetConfig();
    QString magnification;
    if (userMode == 1)
    {
        magnification = object["st zoom"].toArray()[index].toString();
    }
    else
    {
        if(index >= 5)
        {
            magnification = object["lt zoom"].toArray()[4].toString();
        }
        else
        {
            magnification = object["lt zoom"].toArray()[index].toString();
        }
    }
    object = ConfigManager("camera_zoom_mag.json").GetConfig();
    this->zoom_from_pqrs(object.value(magnification).toString());
}

void SerialViscaManager::SetZoomForZoomFocus(int index)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();
    object = ConfigManager("zoom.json").GetConfig();
    QString magnification;

    if(index==5)
    {
        magnification = object["lt zoom"].toArray()[index-1].toString();
    }
    else
    {
        magnification = object["lt zoom"].toArray()[index].toString();
    }

    object = ConfigManager("camera_zoom_mag.json").GetConfig();
    this->zoom_from_pqrs(object.value(magnification).toString());
}

void SerialViscaManager::SetZoomForVmode(int index)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();
    object = ConfigManager("zoom.json").GetConfig();
    QString magnification;

    if(index==5)
    {
        magnification = object["lt zoom"].toArray()[index-1].toString();
    }
    else
    {
        magnification = object["lt zoom"].toArray()[index].toString();
    }

    object = ConfigManager("camera_zoom_mag.json").GetConfig();
    this->zoom_from_pqrs_noFeedback(object.value(magnification).toString());
}

void SerialViscaManager::SetDZoom(int index)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();
    object = ConfigManager("dzoom.json").GetConfig();
    QString pq;
    if (userMode == 1)
    {
        pq = object["st dzoom"].toArray()[index].toString();
    }
    else
    {
        pq = object["lt dzoom"].toArray()[index].toString();

    }
    this->dzoom_from_pq(pq);
}

void SerialViscaManager::SetDZoomForZoomFocus(int index)
{
    QJsonObject object = ConfigManager("parameter_setting1.json").GetConfig();
    int userMode = object["speed selection"].toInt();
    object = ConfigManager("dzoom.json").GetConfig();
    QString pq;

    pq = object["lt dzoom"].toArray()[index].toString();

    object = ConfigManager("camera_zoom_mag.json").GetConfig();
    this->dzoom_from_pq(pq);
}

void SerialViscaManager::SetDayMode(int index, bool bFocus)
{
    ConfigManager config = ConfigManager("exposure.json");
    QJsonObject object = config.GetConfig();
    QJsonObject ret;
    bool bDay = false;
    switch (index) {
    case 1:
    {
        ret = object["Day"].toObject()["Dark"].toObject();
        bDay = true;
    }
        break;
    case 2:
    {
        ret = object["Day"].toObject()["Normal"].toObject();
        bDay = true;
    }
        break;
    case 3:
    {
        ret = object["Day"].toObject()["Bright"].toObject();
        bDay = true;
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
    set_AE_Mode("03");
    set_iris_from_pq(ret["Iris"].toString(), bDay);
    set_shutter_speed_from_pq(ret["Shutter"].toString());
    set_gain_from_pq(ret["Gain"].toString());
    set_AE_Mode(ret["Priority"].toString());
    set_noise_reduction_on(ret["DNR"].toString());
    ret["DIS"].toBool() ? set_DIS_on() : set_DIS_off();
    ret["DEFOG"].toBool() ? set_defog_on() : set_defog_off();
    ret["HLC"].toBool() ? set_HLC_on() : set_HLC_off();
//    set_AE_shutter_priority();
    if (index > 0 && index < 4)
        set_infrared_mode_off();
    else
        set_infrared_mode_on();

    if (bFocus)
    {
        ConfigManager config3 = ConfigManager("parameter_enforcement.json");
        QJsonObject object3 = config3.GetConfig();

        int zoom_index = object3["zoom index"].toInt() - 1;
        SetFocus(zoom_index);
    }
    if(bDay)
    {
        v4l2_thread::getInstance()->setUseFlash(false);
    }
    else
    {
        v4l2_thread::getInstance()->setUseFlash(true);
    }
//    SetZoom
}

void SerialViscaManager::check_OPT_done()
{
    QEventLoop loop;
    connect(visca_packet, SIGNAL(sig_show_focus(QString)), &loop, SLOT(quit()));
    show_focusPosition();
    loop.exec();

    QString qstrFocus = QStringLiteral("%1").arg(getVisca_packet()->m_qstrFocus_pqrs.toInt(nullptr, 16), 4, 16, QLatin1Char('0'));

    m_focus_pqrs = qstrFocus;
    if(m_lastQstrFocus == qstrFocus)
    {
        opt_count++;
        if(opt_count >= CHECK_OPT_DONE_COUNTER)
        {
            m_pTimerCheckOPTdone->stop();

        }
    } else {
        opt_count = 0;
    }
    m_lastQstrFocus = qstrFocus;

//    label_focus_pqrs->setText(qstrFocus);

}


void SerialViscaManager::setZFcontrolThread(int index, int daynight)
{

    // Use QtConcurrent::run to execute the member function in a separate thread
    QFuture<void> future = QtConcurrent::run(this, &SerialViscaManager::SetZoomForVmode, index);
    QFuture<void> future2 = QtConcurrent::run(this, &SerialViscaManager::SetFocusForVmode, index, daynight);
}

QString SerialViscaManager::getFocus_pqrs()
{
    return m_focus_pqrs;
}
