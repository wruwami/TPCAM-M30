#include "SerialViscaManager.h"
#include <QSerialPort>
#include "ViscaPacket.h"

#include <QDebug>

SerialViscaManager::SerialViscaManager()
{
    serial_visca = new QSerialPort(this);
    visca_packet = new ViscaPacket;

    camera_con = 0;
//    connectVisca();
    connect(serial_visca, SIGNAL(readyRead()), this, SLOT(receive_camera()));
}

QString SerialViscaManager::connectVisca()
{
    serial_visca->setPortName("ttyS0");
    serial_visca->setBaudRate(QSerialPort::Baud9600);
    serial_visca->setDataBits(QSerialPort::Data8);
    serial_visca->setParity(QSerialPort::NoParity);
    serial_visca->setStopBits(QSerialPort::OneStop);
    serial_visca->setFlowControl(QSerialPort::NoFlowControl);

    if(camera_con==0)
    {
        if(!serial_visca->open(QIODevice::ReadWrite)){
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
                if(serial_visca->isOpen())
                    serial_visca->close();

                camera_con=0;
                return "Connect";
            }

        }
    }
    else
    {
//        ui->pushButton_visca->setText("Connect");
        if(serial_visca->isOpen())
            serial_visca->close();
        camera_con=0;
        return "Connect";
    }
    return "";
}

void SerialViscaManager::close()
{
    if(serial_visca->isOpen())
        serial_visca->close();
    camera_con=0;
}

void SerialViscaManager::SetViscaValue(ViscaType type)
{

}

void SerialViscaManager::SetViscaValue(ViscaType type, int value)
{

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

     QByteArray data;
     if(visca_packet)
         data= visca_packet->BlockCamMakePacket(header, msg, msgSize);

     qDebug() << data;

     if(serial_visca)
         serial_visca->write(data);
}

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

