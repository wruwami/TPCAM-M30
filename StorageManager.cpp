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
    m_fSDExitEnforcementPercent = object["SD"].toObject()["exit enforcement percent"].toDouble();


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
            isExistEMMccard = true;
        }
    }

    foreach(auto storage , QStorageInfo::mountedVolumes())
    {
        if (QString(storage.device()) == USB)
        {
            m_usbStorage = storage;
            isExistEMMccard = true;
        }
    }
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
    if (GetSDAvailable() / GetSDTotal() * 100  < m_fSDExitSelfTestPercent)
        return true;
    return false;
}

bool StorageManager::GetSDExitEnforcement()
{
    if (GetSDAvailable() / GetSDTotal() * 100 < m_fSDExitEnforcementPercent)
        return true;
    return false;
}

bool StorageManager::GetEMMCExitSelfTest()
{
    if (GeteMMCAvailable() / GeteMMCTotal() * 100 < m_fEMMCExitSelfTestPercent)
        return true;
    return false;
}
