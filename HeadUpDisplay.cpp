#include "HeadUpDisplay.h"

#include <QFile>
#include <QTextStream>
#include <cstdlib>

CHeadUpDisplay::CHeadUpDisplay()
{
    initDisplay();
}

void CHeadUpDisplay::initDisplay()
{
    writeNumberToFile("init", 0);
    writeNumberToFile("display", 0);
    writeNumberToFile("display", 1);
    writeNumberToFile("pointer", 1);

    connect(&m_DistanceTimer, SIGNAL(timeout()), this, SLOT(hideDistance()));
    connect(&m_SpeedTimer, SIGNAL(timeout()), this, SLOT(hideSpeed()));
}

void CHeadUpDisplay::showDistanceSensitivity(float fDistance, int nSensitivity)
{
    if(m_bSensitivityOn)
    {
        if(readNumberFromFile("distance_sensitivity") == 0 || readNumberFromFile("distance_sensitivity_unit") != m_nDistanceUnit)
        {
            writeNumberToFile("clear_content", 1);
            writeNumberToFile("distance_sensitivity_unit", m_nDistanceUnit);
            writeNumberToFile("distance", 0);
            writeNumberToFile("distance_sensitivity", 1);
            writeNumberToFile("pointer", 1);
        }

        writeNumberToFile("distance_sensitivity_distance_value", fDistance*10);
        writeNumberToFile("distance_sensitivity_sensitivity_value", nSensitivity);
    }
    else //m_bSensitivityOn == false
    {
        if(readNumberFromFile("distance") == 0 || readNumberFromFile("distance_unit") != m_nDistanceUnit)
        {
            writeNumberToFile("clear_content", 1);
            writeNumberToFile("distance_unit", m_nDistanceUnit);
            writeNumberToFile("distance_sensitivity", 0);
            writeNumberToFile("distance", 1);
            writeNumberToFile("pointer", 1);
        }

        writeNumberToFile("distance_value", fDistance*10);
    }

    m_DistanceTimer.start(200);
}

void CHeadUpDisplay::showSpeedDistanceSensitivity(float fSpeed, float distance)
{
    if(m_bSensitivityOn)
    {
        if(readNumberFromFile("distance_sensitivity") == 0 || readNumberFromFile("distance_sensitivity_unit") != m_nDistanceUnit)
        {
            writeNumberToFile("clear_content", 1);
            writeNumberToFile("distance_sensitivity_unit", m_nDistanceUnit);
            writeNumberToFile("distance", 0);
            writeNumberToFile("distance_sensitivity", 1);
            writeNumberToFile("pointer", 1);
        }

//        writeNumberToFile("distance_sensitivity_distance_value", distance*10);
    }
    else //m_bSensitivityOn == false
    {
        if(readNumberFromFile("distance") == 0 || readNumberFromFile("distance_unit") != m_nDistanceUnit)
        {
            writeNumberToFile("clear_content", 1);
            writeNumberToFile("distance_unit", m_nDistanceUnit);
            writeNumberToFile("distance_sensitivity", 0);
            writeNumberToFile("distance", 1);
            writeNumberToFile("pointer", 1);
        }

//        writeNumberToFile("distance_value", distance*10);
    }


    writeNumberToFile("speed_value", fSpeed);

    writeNumberToFile("speed", m_nREC);

//    if((fSpeed==0) || (m_SpeedTimer.elapsed()>300))
//    {
//        writeNumberToFile("speed", 0);
//    }
//    else
//    {

//    }
    m_SpeedTimer.start(200);
    m_DistanceTimer.start(200);
}

void CHeadUpDisplay::showCaptureSpeedDistance(float fSpeed, float distance)
{
    if(m_bSensitivityOn)
    {
        if(readNumberFromFile("distance_sensitivity") == 0 || readNumberFromFile("distance_sensitivity_unit") != m_nDistanceUnit)
        {
            writeNumberToFile("clear_content", 1);
            writeNumberToFile("distance_sensitivity_unit", m_nDistanceUnit);
            writeNumberToFile("distance", 0);
            writeNumberToFile("distance_sensitivity", 1);
            writeNumberToFile("pointer", 1);
        }

        writeNumberToFile("distance_sensitivity_distance_value", distance*10);
    }
    else //m_bSensitivityOn == false
    {
        if(readNumberFromFile("distance") == 0 || readNumberFromFile("distance_unit") != m_nDistanceUnit)
        {
            writeNumberToFile("clear_content", 1);
            writeNumberToFile("distance_unit", m_nDistanceUnit);
            writeNumberToFile("distance_sensitivity", 0);
            writeNumberToFile("distance", 1);
            writeNumberToFile("pointer", 1);
        }

        writeNumberToFile("distance_value", distance*10);
    }


    writeNumberToFile("speed_value", fSpeed);

    writeNumberToFile("speed", m_nREC);

//    if((fSpeed==0) || (m_SpeedTimer.elapsed()>300))
//    {
//        writeNumberToFile("speed", 0);
//    }
//    else
//    {

//    }
    m_SpeedTimer.start(600);
    m_DistanceTimer.start(600);
}
void CHeadUpDisplay::hideSpeed()
{
    writeNumberToFile("speed", 0);
}


void CHeadUpDisplay::hideDistance()
{
    if(m_bSensitivityOn)
    {
        writeNumberToFile("distance_sensitivity_distance_value", 0);
    }
    else
    {
        writeNumberToFile("distance_value", 0);
    }
}



//using QFILE

bool CHeadUpDisplay::writeNumberToFile(QString fileName, int value)
{
    QString path = "/sys/devices/platform/hud/";
    QFile file(path+fileName);
    uint8_t ret;

    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream out(&file);
        out << value;
//        ret = file.write(QString::number(value).toUtf8());
        file.close();
        return true;
//        if(ret == 1)
//        {
//        }
    }
    return false;

}

int CHeadUpDisplay::readNumberFromFile(QString fileName)
{
    QString path = "/sys/devices/platform/hud/";
    QFile file(path+fileName);
    int value;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in >> value;
//        ret = file.write(QString::number(value).toUtf8());
        file.close();
        return value;
//        if(ret == 1)
//        {
//        }
    }
    return -1;

}

//using system

//bool CHeadUpDisplay::writeNumberToFile(QString fileName, int value)
//{
//    QString path = "/sys/devices/platform/hud/";
//    QFile file(path+fileName);
//    uint8_t ret;

//    QString cmdLine = "echo firefly | sudo -S echo " + QString::number(value) + " < " + path + fileName;
//    std::system(cmdLine.toStdString().c_str());

//    return true;

//}


void CHeadUpDisplay::changeToSpeedCheckMode()
{
    m_bSensitivityOn = false;//감도를 표시 안해줍니다.
    m_nREC = 2; //화면녹화 표시(REC)를 켜줍니다. (제한속도 이상일 경우만)
    initDisplay();//화면을 껐다 켜고 조준선을 켜줍니다.
}

void CHeadUpDisplay::changeToAlineMode()
{
    m_bSensitivityOn = true;//감도를 표시 해줍니다.
    m_nREC = 1; //화면녹화 표시(REC)를 꺼줍니다.
    initDisplay();//화면을 껐다 켜고 조준선을 켜줍니다.
}






