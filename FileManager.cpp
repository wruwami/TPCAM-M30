#include "FileManager.h"

#include "qdir.h"
#include <QDateTime>
#include <QJsonArray>

#include "DateFormatManager.h"
#include "SerialGPSManager.h"
#include "ConfigManager.h"
#include "StorageManager.h"

#define DEFAULT_FILE_PATH   "/files/"

FileManager* FileManager::instance = nullptr;

extern int g_nCrackDownIndex;

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
        case VISCA_LOG:
    {
        return MakeSDPath("visca_log");
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

QString FileManager::GetFileName(SDPath sdpath)
{
    QDate date = date.currentDate();

    switch (sdpath)
    {
    case LASER_LOG:
    {
        return "laser_log_" + date.toString("yyyyMMdd") + ".txt";
    }
        break;
    case SYSTEM_LOG:
    {
        return "system_log_" + date.toString("yyyyMMdd") + ".txt";
    }
        break;
    case VISCA_LOG:
    {
        return "visca_log_" + date.toString("yyyyMMdd") + ".txt";
    }
        break;

    }
}

QString FileManager::GetFileName(PrefixType prefix)
{
    QDateTime datetime = datetime.currentDateTime();
    if (prefix == SC)
        return "SC_" + datetime.toString("yyyyMMdd_hhmmss") + ".jpg";
    else
        return "SR_" + datetime.toString("yyyyMMdd_hhmmss") + ".avi";
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
//    QDateTime datetime = QDateTime::currentDateTime();
    ConfigManager con = ConfigManager("parameter_login.json");
    QJsonObject object = con.GetConfig();

    ConfigManager con2 = ConfigManager("setting_device_ID.json");
    QJsonObject object2 = con2.GetConfig();
    QJsonObject object3 = object2["Device ID"].toObject();

    QString deviceID;
    if (QString::compare(object3["Prefix"].toString(), "null", Qt::CaseInsensitive) && !object3["Prefix"].toString().isEmpty())
        deviceID.append(object3["Prefix"].toString() + "_" + object3["SerialNum"].toString());
    else
        deviceID.append(object3["SerialNum"].toString());
    if (QString::compare(object3["Postfix"].toString(), "null", Qt::CaseInsensitive) && !object3["Postfix"].toString().isEmpty())
        deviceID.append("_" + object3["Postfix"].toString());

//    int userIndex = object["User Name Select"].toInt() - 1;
//    QJsonArray ar = object["User Name items"].toArray();
    QString userID = FileManager::GetInstance()->userName();
    con = ConfigManager("parameter_setting1.json");
    object = con.GetConfig();
    int locationIndex = object["location selection"].toInt() - 1;
    QString Location = object["location items"].toArray()[locationIndex].toString();

    QString captureSpeed;
    if (enforceInfo.nCaptureSpeed >= 0)
    {
        captureSpeed = "P";
    }
    else
    {
        captureSpeed = "M";
        enforceInfo.nCaptureSpeed = -enforceInfo.nCaptureSpeed;
    }

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
    strZoomIndex.sprintf("%02d", enforceInfo.zoom_index + 1);
    mode.append(strZoomIndex);

    int index = g_nCrackDownIndex; // index
    QString ret;
    ret.sprintf("%s_%05d_%s_%s_%s%04d_%04d_%04d_%04d_%s_%s_%s_%s_%s_%s_S.%s"
                            ,strPrefix.toStdString().c_str()
                            ,index
                            ,enforceInfo.date.toStdString().c_str()
//                            ,QString(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]).toStdString().c_str()
                            ,enforceInfo.time.toStdString().c_str()
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

    ret.replace(" ", "");

    return ret;
}

QString FileManager::GeteMMCPath()
{
    QDir dir;
    return dir.absolutePath()/* + DEFAULT_FILE_PATH*/;
//    StorageManager storageManager;
//    return storageManager.GetEMMCPath();
//    return "/userdata/TPCAM-M30";
}

QString FileManager::GetSDPath()
{
    // sdcard root path
//    QDir dir;
//    return dir.absolutePath();
    StorageManager storageManager;
    return storageManager.GetSDCARDPath();
//    return "/home/wruwami/sdcard";
}

QString FileManager::GetUSBPath()
{
//    QDir dir;
//    return dir.absolutePath();
    StorageManager storageManager;
    return storageManager.GetUSBPath();
//    return "/home/wruwami/usb";
}

QString FileManager::MakeSDPath(QString path)
{
    QDir dir(GetSDPath() + "/" + path);
    if (!dir.exists())
    {
        dir.mkdir(GetSDPath() + "/" + path);
    }

    if (path == "laser_log" || path == "system_log" || path == "visca_log")
        return dir.absolutePath();

    QDateTime datetime = datetime.currentDateTime();
    dir = GetSDPath() + "/" + path + "/" + datetime.toString("yyyyMMddhh");
    if (!dir.exists())
    {
        dir.mkdir(GetSDPath() + "/" + path + "/" + datetime.toString("yyyyMMddhh"));
    }

    return dir.absolutePath();
}

const QString &FileManager::userName() const
{
    return m_userName;
}

void FileManager::setUserName(const QString &newUserName)
{
    m_userName = newUserName;
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
