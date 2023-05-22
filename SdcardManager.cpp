#include "SdcardManager.h"

//#include <QDebug>

SdcardManager::SdcardManager()
{
    foreach(m_storage , QStorageInfo::mountedVolumes())
    {
        if (m_storage.name() == "/dev/mmcblk0p1")
            break;
    }

//    qDebug() << "name:" << m_storage.name();
//    qDebug() << "fileSystemType:" << m_storage.fileSystemType();
//    qDebug() << "size:" << m_storage.bytesTotal()/1024/1024 << "MB";
//    qDebug() << "availableSize:" << m_storage.bytesAvailable()/1024/1024 << "MB";
}

int SdcardManager::GetAvailable()
{
    return m_storage.bytesAvailable()/1024/1024;
}

int SdcardManager::GetTotal()
{
    return m_storage.bytesTotal()/1024/1024;
}
