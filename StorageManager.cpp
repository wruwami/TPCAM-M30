#include "StorageManager.h"

#include <QDebug>
#include "ConfigManager.h"

StorageManager::StorageManager()
{
    ConfigManager configManager = ConfigManager("setting_storage.json");
    QJsonObject object = configManager.GetConfig();
    QString SDCARD = object["SD"].toObject()["name"].toString();
    QString EMMC = object["emmc"].toObject()["name"].toString();
    QString USB = object["USB"].toObject()["name"].toString();
    m_fEMMCExitSelfTestPercent = object["emmc"].toObject()["exit self test percent"].toDouble();
    m_fSDExitSelfTestPercent = object["SD"].toObject()["exit self test percent"].toDouble();
    m_fSDExitEnforcementPercent = object["SD"].toObject()["exit self test percent"].toDouble();


    foreach(auto storage , QStorageInfo::mountedVolumes())
    {
        if (QString(storage.device()) == SDCARD)
        {
            m_sdStorage = storage;
            isExistSdcard = true;
        }
    }

    foreach(auto storage , QStorageInfo::mountedVolumes())
    {
        if (QString(storage.device()) == EMMC)
        {
            m_emmcStorage = storage;
//            storage.mountedVolumes()
            isExistEMMccard = true;
        }
    }

    foreach(auto storage , QStorageInfo::mountedVolumes())
    {
        if (QString(storage.device()) == USB)
        {
            m_usbStorage = storage;
//            storage.mountedVolumes()
            isExistEMMccard = true;
        }
    }

    foreach (auto sdStorage, QStorageInfo::mountedVolumes())
    {
        qDebug() << "displayName : " + sdStorage.displayName();
        qDebug() << "name : " + sdStorage.name();
        qDebug() << "fileSystemType : " + sdStorage.fileSystemType();
        qDebug() << "device : " + sdStorage.device();
    }



//    qDebug() << "name:" << m_storage.name();
//    qDebug() << "fileSystemType:" << m_storage.fileSystemType();
//    qDebug() << "size:" << m_storage.bytesTotal()/1024/1024 << "MB";
//    qDebug() << "availableSize:" << m_storage.bytesAvailable()/1024/1024 << "MB";
}

float StorageManager::GetSDAvailable()
{
    return m_sdStorage.bytesAvailable()/1024/1024;
}

float StorageManager::GetSDTotal()
{
    return m_sdStorage.bytesTotal()/1024/1024;
}

float StorageManager::GeteMMCAvailable()
{
    return m_emmcStorage.bytesAvailable()/1024/1024;
}

float StorageManager::GeteMMCTotal()
{
    return m_emmcStorage.bytesTotal()/1024/1024;
}

QString StorageManager::GetSDCARDPath()
{
    return m_sdStorage.rootPath();
}

QString StorageManager::GetEMMCPath()
{
    return m_emmcStorage.rootPath();
}

QString StorageManager::GetUSBPath()
{
    return m_usbStorage.rootPath();
}

bool StorageManager::GetSDExitSelfTest()
{
    if (GetSDAvailable() < m_fSDExitSelfTestPercent)
        return true;
    return false;
}

bool StorageManager::GetSDExitEnforcement()
{
    if (GetSDAvailable() < m_fSDExitEnforcementPercent)
        return true;
    return false;
}

bool StorageManager::GetEMMCExitSelfTest()
{
    if (GeteMMCAvailable() < m_fEMMCExitSelfTestPercent)
        return true;
    return false;
}
