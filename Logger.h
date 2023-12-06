/**
 * @file Logger.h
 * @author wruwami (wruwami@naver.com)
 * @brief Log를 관리하는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

//enum LogType
//{
//    LaserLogType,
//    SystemLogType,
//};

enum ViscaLogType
{
    VISCA_RECEIVE_DATA,
    VISCA_SEND_DATA,
};

enum LaserLogType
{
    LASER_RECEIVE_DATA,
    LASER_SEND_DATA,
};

enum SystemLogType
{
    POWER_ON,
    POWER_OFF,
    BATTERY_STATUS,
    SELF_TEST,
    GPS_DETECTED,
    NETWORK_CONNECTED,
    NETWORK_DISCONNECTED,
    ENTERED_MENU,
    BUTTON_CLICKED,
    INDICATOR_CLICKED,
    FILE_MANAGER,
    DEFAULT,

};

class Logger
{
private:
    Logger() {}
    Logger(const Logger& other);
    ~Logger() {}
    static Logger* instance;
    QString GetLogHeader();
public:
    static Logger* GetInstance()
    {
        if(instance == nullptr) instance = new Logger();
        return instance;
    }
    void SetLogMsg(LaserLogType, QString = "");
    void SetLogMsg(SystemLogType, QString = "");
    void SetLogMsg(ViscaLogType, QString = "");

};

static void SetLogMsg(LaserLogType logType, QString msg = "")
{
    return Logger::GetInstance()->SetLogMsg(logType, msg);
}

static void SetLogMsg(ViscaLogType logType, QString msg = "")
{
    return Logger::GetInstance()->SetLogMsg(logType, msg);
}


static void SetLogMsg(SystemLogType logType, QString msg = "")
{
    return Logger::GetInstance()->SetLogMsg(logType, msg);
}


#endif // LOGGER_H
