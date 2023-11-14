#include "SerialGPSManager.h"

#include <QSerialPort>
#include <QDebug>
#include <math.h>
#include "Logger.h"

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

SerialGPSManager* SerialGPSManager::instance = nullptr;


SerialGPSManager::SerialGPSManager()
{
    m_pSerial = new QSerialPort(this);

    serial_connect();
    connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(serial_received()));

    m_DateTime = QDateTime::currentDateTime();
}

void SerialGPSManager::serial_connect()
{
    m_pSerial->setPortName("ttyUSB0");
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

QString SerialGPSManager::GetDateTimeString()
{
    return m_DateTime.toString("yyyy-MM-dd hh:mm:ss");
}

QDateTime SerialGPSManager::GetDateTime()
{
    return m_DateTime;
}

int SerialGPSManager::GetSatellitesInView()
{
    return m_nSatellitesInView;
}

QString SerialGPSManager::GetLatitude()
{
    QString latitude = m_Latitude.mid(1,-1);
    if(latitude == "000.000000")
        return "";
    return m_Latitude;
}

QString SerialGPSManager::GetLongitude()
{
    QString longitude = m_Longitude.mid(1,-1);
    if(longitude == "000.000000")
        return "";
    return m_Longitude;
}

float SerialGPSManager::GetLatitudeValue()
{
    return m_fLatitude;
}

float SerialGPSManager::GetLongitudeValue()
{
    return m_fLongitude;
}


QString SerialGPSManager::GetSensitivity()
{
    return m_sensitivity;
}



void SerialGPSManager::serial_received()
{
    QString received;
    gprmc_data datum;
    while (m_pSerial->canReadLine()){
        received = m_pSerial->readLine();  //reads in data line by line, separated by \n or \r characters
    }
    QStringList splitted = received.split(",");
    if (splitted.value(0) == "$GPRMC" || splitted.value(0) == "$GNRMC"){
//        qDebug() << received;
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
        datum.A_hora = (int)splitted[1].toFloat();
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


        if (datum.B_warning == 'V')
            return;
        QString time_format = "ddMMyyHHmmss";
        QString time = splitted[1].mid(0, splitted[1].indexOf("."));
        QString date = splitted[9];
        m_DateTime = QDateTime::fromString(date+time, time_format);
        m_DateTime = m_DateTime.addYears(100);
        m_fLatitude = changeMinuteToDegree(splitted[3]).toFloat();
        m_fLongitude = changeMinuteToDegree(splitted[5]).toFloat();

        m_Latitude = splitted[4] + changeMinuteToDegree(splitted[3]);
        m_Longitude = splitted[6] + changeMinuteToDegree(splitted[5]);

        //TTFF 계산

        if((m_nTTFFFlag == 0) && (splitted[2] == "A"))
        {
            m_nTTFF = m_timer.elapsed();
            m_nTTFFFlag = 1;
        }
    }
    else if(splitted.value(0) == "$GPGSV" || splitted.value(0) == "$GNGSV")
    {
        QString number;
        QString snr;
        int snr_ary[7];
//        qDebug() << received;
        if(splitted.value(3).contains("*", Qt::CaseInsensitive))
        {
            number ="";
        }
        else
        {
            number =splitted.value(3);
        }
        if(splitted.value(7).contains("*", Qt::CaseInsensitive))
        {
            snr ="";
        }
        else
        {
            snr =splitted.value(7);
        }
        for(int l = 0; l<7; l++)
        {
            snr_ary[l] = splitted.value(7+l*4).toInt();
        }
        m_nSatellitesInView = splitted.value(1).toUInt();
        if (m_nSatellitesInView >= 3 && m_bFirstLog)
        {
            QString msg;
            msg = m_Latitude + "," + m_Longitude + "," + m_DateTime.toString("hh:mm:ss");
            SetLogMsg(GPS_DETECTED, msg);
        }
        m_sensitivity = splitted.value(7);
//        qDebug() << "Number of Message: "+splitted.value(1);
//        qDebug() << "Message Number: "+splitted.value(2);
//        qDebug() << "Satellites in View: "+splitted.value(3);
//        qDebug() << "1SNR(dBHz]: "+ splitted.value(7);
//        qDebug() << "2SNR(dBHz]: "+ splitted.value(7+4);
//        qDebug() << "3SNR(dBHz]: "+ splitted.value(7+4+4);
//        qDebug() << "4SNR(dBHz]: "+ splitted.value(7+4+4+4);
        //(int)splitted[3].toInt();//Satellites Used(0~12)
    }

}

QString SerialGPSManager::changeMinuteToDegree(QString Minute)
{
    QString Degree;
    int nDegree;
    double dDegree;

    nDegree = Minute.toDouble()/100;
    dDegree = fmod(Minute.toDouble(), 100) / 60.0;

    if (nDegree+dDegree)
        Degree = "+";
    else
        Degree = "-";
    Degree.append(QString::number(nDegree+dDegree, 'f', 6));
    return Degree;
}
