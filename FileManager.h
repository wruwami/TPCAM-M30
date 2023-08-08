#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

enum Type
{
    eMMC,
    SD,
    USB,
};

enum PrefixType
{
    AI,
    AV,
    VV,
    SC,
    SR,
    MC,
};

enum SDPath {
    ATEXT,
    AUTO,
    FACTORY,
    LASER_LOG,
    MANUAL_CAPTURE,
    SCREEN,
    SNAPSHOT,
    SYSTEM_LOG,
    VIDEO,
};

typedef struct _ST_ENFORCEMENT_INFO
{
    int nCaptureSpeed;
    int nSpeedLimit;
    int nCaptureSpeedLimit;
    int nDistance;
    bool bUserMode;
    int enforceMode; //0 : I, 1 : A, 2: V
    int vehicle; //0 : normal , 1 : truck, 2: motocycle
    int zoom_index;
//    QString strMode;
//    QString strLatitude;
//    QString strLongitude;
//    QString strLocation;
//    QString strUserID;
//    QString strDeviceId;
//    QString strUnit = "S";

    void operator=(_ST_ENFORCEMENT_INFO& enforceInfo)
    {
        this->nCaptureSpeed = enforceInfo.nCaptureSpeed;
        this->nSpeedLimit = enforceInfo.nSpeedLimit;
        this->nCaptureSpeedLimit = enforceInfo.nCaptureSpeedLimit;
        this->nDistance = enforceInfo.nDistance;
        this->bUserMode = enforceInfo.bUserMode;
        this->enforceMode = enforceInfo.enforceMode; //0 : I, 1 : A, 2: V
        this->vehicle = enforceInfo.vehicle; //0 : normal , 1 : truck, 2: motocycle
        this->zoom_index = enforceInfo.zoom_index;
    }
}stEnforcementInfo;


class FileManager
{
private:
    FileManager() {}
    FileManager(const FileManager& other);
    ~FileManager() {}
    static FileManager* instance;
public:
    static FileManager* GetInstance()
    {
        if(instance == nullptr) instance = new FileManager();
        return instance;
    }
    QString GetPath(QString name,Type type);
    QString GetSubPath(QString name,Type type);
    QString GetSDPath(SDPath);
    QString AddFile(QString path_name, QString file_name);
    QString GetFileName(PrefixType prefix);
    QString GetFileName(PrefixType prefix, stEnforcementInfo enforceInfo);

    QString GeteMMCPath();
    QString GetSDPath();
    QString GetUSBPath();
private:
    QString MakeSDPath(QString);

//private:
//    QString GetDeviceID(QJsonObject);
};

static QString GetPath(QString name, Type type)
{
    return FileManager::GetInstance()->GetPath(name, type);
}
static QString AddFile(QString path_name, QString file_name)
{
    return FileManager::GetInstance()->AddFile(path_name, file_name);
}
static QString GetSubPath(QString name, Type type)
{
    return FileManager::GetInstance()->GetSubPath(name, type);
}
static QString GetFileName(PrefixType prefix)
{
    return FileManager::GetInstance()->GetFileName(prefix);
}
static QString GetFileName(PrefixType prefix, stEnforcementInfo enforceInfo)
{
    return FileManager::GetInstance()->GetFileName(prefix, enforceInfo);
}
static QString GeteMMCPath()
{
    return FileManager::GetInstance()->GeteMMCPath();
}

static QString GetSDPath()
{
    return FileManager::GetInstance()->GetSDPath();
}

static QString GetUSBPath()
{
    return FileManager::GetInstance()->GetUSBPath();
}

static QString GETSDPATH(SDPath sdPath)
{
    return FileManager::GetInstance()->GetSDPath(sdPath);
}

#endif // FILEMANAGER_H
