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
}

void CHeadUpDisplay::showSpeedDistance(int speed, float distance)
{
//    writeNumberToFile("distance", 1);
//    if(speed==0)
//    {
//        writeNumberToFile("speed", 0);
//    }
//    else
//    {
//        writeNumberToFile("speed", 1);
//    }

//    writeNumberToFile("distance_value", distance);
//    writeNumberToFile("speed_value", speed);


    writeNumberToFile("distance", 1);
    if((speed==0) || (m_SpeedTimer.elapsed()>500))
    {
        writeNumberToFile("speed", 0);
    }
    else
    {
        writeNumberToFile("speed", 2);
    }

    writeNumberToFile("distance_value", distance);
    writeNumberToFile("speed_value", speed);

    if(speed != m_fPastSpeed)
    {
        m_SpeedTimer.start();
    }

    m_fPastSpeed = speed;
}

void CHeadUpDisplay::showSpeedDistanceSensitivity(int speed, float distance, int sensitivity)
{

    if((speed==0) || (m_SpeedTimer.elapsed()>500))
    {
        writeNumberToFile("speed", 0);
    }
    else
    {
        writeNumberToFile("speed", 2);
    }

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
        writeNumberToFile("distance_sensitivity_sensitivity_value", sensitivity);
        writeNumberToFile("speed_value", speed);
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
        writeNumberToFile("speed_value", speed);
    }


    if(speed != m_fPastSpeed)
    {
        m_SpeedTimer.start();
    }

    m_fPastSpeed = speed;
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
