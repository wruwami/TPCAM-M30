#include "SdcardManager.h"

#include <QDebug>

SdcardManager::SdcardManager()
{
    foreach(m_sdStorage , QStorageInfo::mountedVolumes())
    {
        if (m_sdStorage.displayName() == "/dev/mmcblk0p1")
        {
            isExistSdcard = true;
        }
    }

    foreach(m_sdStorage , QStorageInfo::mountedVolumes())
    {
        if (m_emmcStorage.displayName() == "/")
        {
            isExistEMMccard = true;
        }
    }

//    qDebug() << "name:" << m_storage.name();
//    qDebug() << "fileSystemType:" << m_storage.fileSystemType();
//    qDebug() << "size:" << m_storage.bytesTotal()/1024/1024 << "MB";
//    qDebug() << "availableSize:" << m_storage.bytesAvailable()/1024/1024 << "MB";
}

int SdcardManager::GetSDAvailable()
{
    return m_sdStorage.bytesAvailable()/1024/1024;
}

int SdcardManager::GetSDTotal()
{
    return m_sdStorage.bytesTotal()/1024/1024;
}

int SdcardManager::GeteMMCAvailable()
{
    return m_emmcStorage.bytesAvailable()/1024/1024;
}

int SdcardManager::GeteMMCTotal()
{
    return m_emmcStorage.bytesTotal()/1024/1024;
}
