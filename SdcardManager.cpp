#include "SdcardManager.h"

#include <QDebug>

SdcardManager::SdcardManager()
{
    foreach(auto storage , QStorageInfo::mountedVolumes())
    {
        if (storage.device() == "/dev/mmcblk0p1")
        {
            m_sdStorage = storage;
            isExistSdcard = true;
        }
    }

    foreach(auto storage , QStorageInfo::mountedVolumes())
    {
        if (storage.device() == "/dev/mmcblk1p8")
        {
            m_emmcStorage = storage;
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

float SdcardManager::GetSDAvailable()
{
    return m_sdStorage.bytesAvailable()/1024/1024;
}

float SdcardManager::GetSDTotal()
{
    return m_sdStorage.bytesTotal()/1024/1024;
}

float SdcardManager::GeteMMCAvailable()
{
    return m_emmcStorage.bytesAvailable()/1024/1024;
}

float SdcardManager::GeteMMCTotal()
{
    return m_emmcStorage.bytesTotal()/1024/1024;
}
