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
    switch (sdPath)
    {
        case ATEXT:
    {
        return MakeSDPath("atext");
    }
        break;
    {
        case AUTO:
    {
        return MakeSDPath("auto");
    }
        break;
        case FACTORY:
    {
        return MakeSDPath("factory");
    }
        break;
        case LASER_LOG:
    {
        return MakeSDPath("laser_log");
    }
        break;
        case MANUAL_CAPTURE:
    {
        return MakeSDPath("manual_capture");
    }
        break;
        case SCREEN:
    {
        return MakeSDPath("screen");
    }
        break;
        case SNAPSHOT:
    {
        return MakeSDPath("snapshot");
    }
        break;
        case SYSTEM_LOG:
    {
        return MakeSDPath("system_log");
    }
        break;
        case VIDEO:
    {
        return MakeSDPath("video");
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
    QDateTime datetime = datetime.currentDateTime();
    if (prefix == SC)
        return "SC " + datetime.toString("yyyymmdd_hhmmss") + ".jpg";
    else
        return "SR " + datetime.toString("yyyymmdd_hhmmss") + ".avi";
}

QString FileManager::GetFileName(PrefixType prefix, stEnforcementInfo enforceInfo)
{
    QString strPrefix;
    QString extention;
    switch(prefix)
    {
    case AI:
    {
        strPrefix = "AI";
        extention = "jpg";
    }
        break;
    case AV:
    {
        strPrefix = "AV";
        extention = "avi";
    }
        break;
    case VV:
    {
        strPrefix = "VV";
        extention = "avi";
    }
        break;
    case MC:
    {
        strPrefix = "MC";
        extention = "jpg";
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

    QString mode;
    if (enforceInfo.bUserMode)
    {
        mode.append("U");
    }
    else
    {
        mode.append("N");
    }

    switch (enforceInfo.enforceMode)
    {
    case 0:
    {
        mode.append("I");
    }
        break;
    case 1:
    {
        mode.append("A");
    }
        break;
    case 2:
    {
        mode.append("V");
    }
        break;
    }

    switch (enforceInfo.vehicle)
    {
    case 0:
    {
        mode.append("N");
    }
        break;
    case 1:
    {
        mode.append("T");
    }
        break;
    case 2:
    {
        mode.append("M");
    }
        break;
    }
    QString strZoomIndex;
    strZoomIndex.sprintf("%02d", enforceInfo.zoom_index);
    mode.append(strZoomIndex);

    int index = 0; // index
    QString ret;
    ret.sprintf("%s_%05d_%s_%s_%s%04d_%04d_%04d_%04d_%s_%s_%s_%s_%s_%s_S.%s"
                            ,strPrefix.toStdString().c_str()
                            ,index
                            ,datetime.toString("yyyyMMdd").toStdString().c_str()
                            ,QString(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]).toStdString().c_str()
                            ,captureSpeed.toStdString().c_str()
                            ,enforceInfo.nCaptureSpeed
                            ,enforceInfo.nSpeedLimit
                            ,enforceInfo.nCaptureSpeedLimit
                            ,enforceInfo.nDistance
                            ,mode.toStdString().c_str()
                            ,(SerialGPSManager::GetInstance()->GetLatitude()).toStdString().c_str()
                            ,(SerialGPSManager::GetInstance()->GetLongitude()).toStdString().c_str()
                            ,(Location).toStdString().c_str()
                            ,(deviceID).toStdString().c_str()
                            ,(userID).toStdString().c_str()
                            ,extention.toStdString().c_str());







//            QString("%1_%2_%3_%4_%5_%6_%7_%8_%9_%10_%11_%12_%13_%14_%15") \
//            .arg(strPrefix) \
//            .arg((QString::number(index)), 5) \
//            .arg(datetime.toString("yyyyMMdd")) \
//            .arg(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]) \
//            .arg(captureSpeed, 5) \
//            .arg(QString::number(enforceInfo.nSpeedLimit), 4) \
//            .arg(QString::number(enforceInfo.nCaptureSpeedLimit), 4) \
//            .arg(QString::number(enforceInfo.nDistance), 4) \
//            .arg(mode) \
//            .arg(SerialGPSManager::GetInstance()->GetLatitude()) \
//            .arg(SerialGPSManager::GetInstance()->GetLongitude()) \
//            .arg(Location) \
//            .arg(deviceID) \
//            .arg(userID) \
//            .arg("S");

    return ret;
}

QString FileManager::GeteMMCPath()
{
    QDir dir;
    return dir.absolutePath() + DEFAULT_FILE_PATH;
}

QString FileManager::GetSDPath()
{
    // sdcard root path
    QDir dir;
    return dir.absolutePath();
}

QString FileManager::GetUSBPath()
{
    QDir dir;
    return dir.absolutePath();
}

QString FileManager::MakeSDPath(QString path)
{
    QDir dir(GetSDPath() + "/" + path);
    if (!dir.exists())
    {
        dir.mkdir(GetSDPath() + "/" + path);
    }

    if (path == "laser_log" || path == "system_log")
        return dir.absolutePath();

    QDateTime datetime = datetime.currentDateTime();
    dir = GetSDPath() + "/" + path + "/" + datetime.toString("yyyyMMddhh");
    if (!dir.exists())
    {
        dir.mkdir(GetSDPath() + "/" + path + "/" + datetime.toString("yyyyMMddhh"));
    }

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
