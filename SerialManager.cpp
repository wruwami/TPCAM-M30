#include "SerialManager.h"

#include <QSerialPort>
#include <QDebug>

struct gprmc_data
{
    //Recommended minimum specific GPS/Transit data
    int A_hora=-1;
    char B_warning=-1;
    float C_latitude=-1;
    char D_latitude_coord=-1;
    float E_longitude=-1;
    char F_longitude_coord=-1;
    float G_velocidade_nos=-1;
    float H_CMG=-1;
    int I_data=-1;
    float J_variacao_magnetica=-1;
    char K_variacao_magnetica_coord=-1;
};


SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
    m_pSerial = new QSerialPort(this);

    serial_connect();
    connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(serial_received()));
}

void SerialManager::serial_connect()
{
    m_pSerial->setPortName("TTYUSB0");
    m_pSerial->setBaudRate(QSerialPort::Baud9600);
    m_pSerial->setDataBits(QSerialPort::Data8);
    m_pSerial->setParity(QSerialPort::NoParity);
    m_pSerial->setStopBits(QSerialPort::OneStop);
    m_pSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(con==0)
    {
        if(!m_pSerial->open(QIODevice::ReadWrite)){
            //                qDebug() << "Serial port open error";
        }
        else
        {
            if(con==0)
            {
                con=1;
                m_timer.start();
                m_nTTFFFlag = 0;
            }
            else
            {
                if(m_pSerial->isOpen())
                    m_pSerial->close();

                con=0;
            }
        }
    }
    else
    {
        if(m_pSerial->isOpen())
            m_pSerial->close();

        con=0;
    }
}

void SerialManager::serial_received()
{
    QString received;
    gprmc_data datum;
    while (m_pSerial->canReadLine()){
        received = m_pSerial->readLine();  //reads in data line by line, separated by \n or \r characters
    }
    QStringList splitted = received.split(",");
    if (splitted.value(0) == "$GPRMC" || splitted.value(0) == "$GNRMC"){
        qDebug() << received;
        // [Field 1] "hhmmss" - Time of fix UTC
        // [Field 2] Navigation receiver warning A = OK, V = warning
        // [Field 3] Latitude
        // [Field 4] N/S Indicator, N = north, S = south
        // [Field 5] Longitude
        // [Field 6] E/W Indicator, E = east, W = west
        // [Field 7] Speed over ground, Knots
        // [Field 9] "ddmmyy" Date of fix
//        QString gmt_time = ui->textEdit->toPlainText();
//        gmt_time.replace(":", "");
//        float gmt = gmt_time.toFloat();
//        datum.A_hora = (int)splitted[1].toFloat()+(gmt*100);
        datum.B_warning = splitted[2].toStdString()[0];
        datum.C_latitude = splitted[3].toFloat();
        datum.D_latitude_coord = splitted[4].toStdString()[0];
        datum.E_longitude = splitted[5].toFloat();
        datum.F_longitude_coord = splitted[6].toStdString()[0];
        datum.G_velocidade_nos = splitted[7].toFloat();
        datum.H_CMG = splitted[8].toFloat();
        datum.I_data = splitted[9].toInt();
        datum.J_variacao_magnetica = splitted[10].toFloat();
        datum.K_variacao_magnetica_coord = splitted[11].toStdString()[0];
        QString localTime;
        localTime=QString::number( datum.A_hora);

        //TTFF 계산

        if((m_nTTFFFlag == 0) && (splitted[2] == "A"))
        {
            m_nTTFF = m_timer.elapsed();
            m_nTTFFFlag = 1;
        }
//        qDebug() << datum.A_hora;
//        qDebug() << datum.B_warning ;
//        qDebug() << datum.C_latitude;
//        qDebug() << datum.D_latitude_coord;
//        qDebug() << datum.E_longitude;
//        qDebug() << datum.F_longitude_coord;
//        qDebug() << datum.G_velocidade_nos;
//        qDebug() << datum.H_CMG;
//        qDebug() << datum.I_data;
//        qDebug() << datum.J_variacao_magnetica;
//        qDebug() << datum.K_variacao_magnetica_coord;

        // [Field 1] "hhmmss" - Time of fix UTC
        // [Field 2] Navigation receiver warning A = OK, V = warning
        // [Field 3] Latitude
        // [Field 4] N/S Indicator, N = north, S = south
        // [Field 5] Longitude
        // [Field 6] E/W Indicator, E = east, W = west
        // [Field 7] Speed over ground, Knots
        // [Field 9] "ddmmyy" Date of fix

//        model->clear();
//        model->appendRow(new QStandardItem("Satellites in View: "+ number ));
//        model->appendRow(new QStandardItem("SNR: "+ snr ));
//        model->appendRow(new QStandardItem("hhmmss: "+ localTime));
//        model->appendRow(new QStandardItem("Navigation receiver warning: "+splitted[2]));
//        model->appendRow(new QStandardItem("Latitude: "+splitted[3]+splitted[4]));
//        //model->appendRow(new QStandardItem("N/S Indicator: "+splitted[4]));
//        model->appendRow(new QStandardItem("Longitude: "+splitted[5]+splitted[6]));
//        model->appendRow(new QStandardItem("ddMMyy: "+splitted[9]));
//        model->appendRow(new QStandardItem("TTFF: "+QString::number(m_nTTFF)));

//        for(int l =0; l<7; l++)
//        {
//            if(snr_ary[l])
//            {
//                model->appendRow(new QStandardItem("snr"+QString::number(l+1)+": " + QString::number(snr_ary[l])));
//            }
//        }

//        int rowCnt = model->rowCount();
//        for(int i=0;i<rowCnt;i++)
//        {
//            QBrush qBrush;
//            if(0 == (i % 2))
//            {
//                qBrush = QBrush(QColor(212, 244, 250, 255));
//                }
//            else {
//                qBrush = QBrush(QColor(246, 246, 246, 255));
//                }
//            model->setData(model->index(i, 0), qBrush, Qt::BackgroundColorRole);
//        }
//        ui->listView->setModel(model);

//    }
//    else if(splitted.value(0) == "$GPGSV" || splitted.value(0) == "$GNGSV")
//    {
//        qDebug() << received;
//        if(splitted.value(3).contains("*", Qt::CaseInsensitive))
//        {
//            number ="";
//        }
//        else
//        {
//            number =splitted.value(3);
//        }
//        if(splitted.value(7).contains("*", Qt::CaseInsensitive))
//        {
//            snr ="";
//        }
//        else
//        {
//            snr =splitted.value(7);
//        }
//        for(int l = 0; l<7; l++)
//        {
//            snr_ary[l] = splitted.value(7+l*4).toInt();
//        }

//        qDebug() << "Number of Message: "+splitted.value(1);
//        qDebug() << "Message Number: "+splitted.value(2);
//        qDebug() << "Satellites in View: "+splitted.value(3);
//        qDebug() << "1SNR(dBHz]: "+ splitted.value(7);
//        qDebug() << "2SNR(dBHz]: "+ splitted.value(7+4);
//        qDebug() << "3SNR(dBHz]: "+ splitted.value(7+4+4);
//        qDebug() << "4SNR(dBHz]: "+ splitted.value(7+4+4+4);
//        //(int)splitted[3].toInt();//Satellites Used(0~12)
    }

}
