#include "FileManager.h"

#include "qdir.h"
#include <QDateTime>
#include <QJsonArray>

#include "DateFormatManager.h"
#include "SerialGPSManager.h"
#include "ConfigManager.h"

#define DEFAULT_FILE_PATH   "/files/"

FileManager* FileManager::instance = nullptr;

QString FileManager::GetPath(QString name,Type type)
{
    QDir dir;
    if (type == eMMC)
    {
        dir = GeteMMCPath() + name;
        if (!dir.exists())
            dir.mkdir(GeteMMCPath() + name);
        return GeteMMCPath() + name;
    }
    dir = GetSDPath() + name;
    if (!dir.exists())
        dir.mkdir(GetSDPath() + name);
    return GetSDPath() + name;
}

QString FileManager::GetSubPath(QString name,Type type)
{
    QDateTime datetime = datetime.currentDateTime();
    QDir dir;

    if (type == eMMC)
    {
        dir = GeteMMCPath() + name;
        if (!dir.exists())
            dir.mkdir(GeteMMCPath() + name);
        dir = GeteMMCPath() + name + "/" + datetime.toString("yyyyMMdd_hh");
    }
    else
    {
        dir = GetSDPath() + name;
        if (!dir.exists())
            dir.mkdir(GetSDPath() + name);
        dir = GetSDPath() + name + "/" + datetime.toString("yyyyMMdd_hh");
    }   //    QDir dir(GetFirstPath() + name + "/");
    if (!dir.exists())
    {
        if (type == eMMC)
            dir.mkdir(GeteMMCPath() + name + "/" + datetime.toString("yyyyMMdd_hh"));
        else
            dir.mkdir(GetSDPath() + name + "/" + datetime.toString("yyyyMMdd_hh"));
    }
    return dir.absolutePath();
}

QString FileManager::GetSDPath(SDPath sdPath)
{
    QString path = GetSDPath();
    switch (sdPath)
    {
        case ATEXT:
    {

    }
        break;
    {
        case AUTO:
    {

    }
        break;
        case FACTORY:
    {

    }
        break;
        case LASER_LOG:
    {

    }
        break;
        case MANUAL_CAPTURE:
    {

    }
        break;
        case SCREEN:
    {

    }
        break;
        case SNAPSHOT:
    {

    }
        break;
        case SYSTEM_LOG:
    {

    }
        break;
        case VIDEO:
    {

    }
        break;
    }
}
}

QString FileManager::AddFile(QString path_name, QString file_name)
{

}

QString FileManager::GetFileName(PrefixType prefix)
{
    QTime time = time.currentTime();
    if (prefix == SC)
        return "SC " + time.toString("mmss") + ".png";
    else
        return "SR " + time.toString("mmss") + ".mkv";
}

QString FileManager::GetFileName(PrefixType prefix, stEnforcementInfo enforceInfo)
{
    QString strPrefix;
    switch(prefix)
    {
    case AI:
    {
        strPrefix = "AI";
    }
        break;
    case AV:
    {
        strPrefix = "AV";
    }
        break;
    case VV:
    {
        strPrefix = "VV";
    }
        break;
    default:
    {

    }
    break;

    }
//    int nCaptureSpeed;
//    int nSpeedLimit;
//    int nCaptureSpeedLimit;
//    int nDistance;
//    QString strMode;
    QDateTime datetime = QDateTime::currentDateTime();
    ConfigManager con = ConfigManager("parameter_login.json");
    QJsonObject object = con.GetConfig();

    QString deviceID = object["Device ID"].toString();
    int userIndex = object["User Name Select"].toInt() - 1;
    QJsonArray ar = object["User Name items"].toArray();
    QString userID = ar[userIndex].toString();
    con = ConfigManager("parameter_setting1.json");
    object = con.GetConfig();
    int locationIndex = object["location selection"].toInt() - 1;
    QString Location = object["location items"].toArray()[locationIndex].toString();

    QString captureSpeed;
    if (enforceInfo.nCaptureSpeed >= 0)
        captureSpeed = "P" + QString::number(enforceInfo.nCaptureSpeed);
    else
        captureSpeed = "M" + QString::number(enforceInfo.nCaptureSpeed);

    int index = 0; // index
    QString ret = QString("%1_%2_%3_%4_%5_%6_%7_%8_%9_%10_%11_%12_%13_%14_%15").arg(strPrefix) \
            .arg((QString::number(index)), 5) \
            .arg(datetime.toString("yyyyMMdd")) \
            .arg(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]) \
            .arg(captureSpeed, 5) \
            .arg(QString::number(enforceInfo.nSpeedLimit), 4) \
            .arg(QString::number(enforceInfo.nCaptureSpeedLimit), 4) \
            .arg(QString::number(enforceInfo.nDistance), 4) \
            .arg(enforceInfo.strMode) \
            .arg(SerialGPSManager::GetInstance()->GetLatitude()) \
            .arg(SerialGPSManager::GetInstance()->GetLongitude()) \
            .arg(Location) \
            .arg(deviceID) \
            .arg(userID) \
            .arg("S");

    return ret;
}

QString FileManager::GeteMMCPath()
{
    QDir dir;
    return dir.absolutePath() + DEFAULT_FILE_PATH;
}

QString FileManager::GetSDPath()
{
    QDir dir;
    return dir.absolutePath();
}

QString FileManager::GetUSBPath()
{
    QDir dir;
    return dir.absolutePath();
}

//QString FileManager::GetDeviceID(QJsonObject object)
//{
//    QString ret;
//    QString Prefix = object["Prefix"].toString();
//    QString SerialNum = object["SerialNum"].toString();
//    QString Postfix =  object["Postfix"].toString();

//    if (Prefix != "null")
//        ret.append(Prefix + "-");
//    ret.append(SerialNum);
//    if (Postfix != "null")
//        ret.append("-" + Postfix);

//    return ret;
//}
