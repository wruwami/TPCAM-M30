#include "Logger.h"

#include <QFile>
#include <QTime>

#include "FileManager.h"

Logger* Logger::instance = nullptr;

QString Logger::GetLogHeader()
{
    QTime time = time.currentTime();
    return "[" + time.toString("hh:mm:ss") + "] ";
}

void Logger::SetLogMsg(LaserLogType logType, QString msg)
{
    QString logString = GetLogHeader();
    switch (logType)
    {
    case LASER_RECEIVE_DATA:
    {
        logString.append("RX_" + msg + "\n");
    }
        break;
    case LASER_SEND_DATA:
    {
        logString.append("TX_" + msg + "\n");
    }
        break;
    }
    QString full_file_name = GETSDPATH(LASER_LOG) + "/" +  GetFileName(LASER_LOG);
    QFile file(full_file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        file.write(logString.toStdString().c_str(), logString.size());
    }
}

void Logger::SetLogMsg(SystemLogType logType, QString msg)
{
    QString logString = GetLogHeader();
    switch (logType)
    {
    case POWER_ON:
    {
        logString.append("POWER_ON" + msg + "\n");
    }
        break;
    case POWER_OFF:
    {
        logString.append("POWER_OFF" + msg + "\n");
    }
        break;
    case BATTERY_STATUS:
    {
        logString.append("BATTERY_STATUS : " + msg + "\n");
    }
        break;
    case SELF_TEST:
    {
        logString.append("SELF_TEST : " + msg + "\n");
    }
        break;
    case GPS_DETECTED:
    {
        logString.append("GPS_DETECTED : " + msg + "\n");
    }
        break;
    case NETWORK_CONNECTED:
    {
        logString.append("NETWORK_CONNECTED : " + msg + "\n");
    }
        break;
    case NETWORK_DISCONNECTED:
    {
        logString.append("NETWORK_DISCONNECTED : " + msg + "\n");
    }
        break;
    case ENTERED_MENU:
    {
        logString.append("ENTERED_MENU : " + msg + "\n");
    }
        break;
    case BUTTON_CLICKED:
    {
        logString.append("BUTTON_CLICKED : " + msg + "\n");
    }
        break;
    case INDICATOR_CLICKED:
    {
        logString.append("INDICATOR_CLICKED : " + msg + "\n");
    }
        break;
    case FILE_MANAGER:
    {
        logString.append("FILE_MANAGER : " + msg + "\n");
    }
        break;
    case DEFAULT:
    {
        logString.append(msg + "\n");
    }
        break;
    }
    QString full_file_name = GETSDPATH(SYSTEM_LOG) + "/" +  GetFileName(SYSTEM_LOG);
    QFile file(full_file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        file.write(logString.toStdString().c_str(), logString.size());
    }
}

void Logger::SetLogMsg(ViscaLogType logType, QString  msg)
{
    QString logString = GetLogHeader();
    switch (logType)
    {
    case VISCA_RECEIVE_DATA:
    {
        logString.append("RX_" + msg + "\n");
    }
        break;
    case VISCA_SEND_DATA:
    {
        logString.append("TX_" + msg + "\n");
    }
        break;
    }
    QString full_file_name = GETSDPATH(VISCA_LOG) + "/" +  GetFileName(VISCA_LOG);
    QFile file(full_file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        file.write(logString.toStdString().c_str(), logString.size());
    }

}
