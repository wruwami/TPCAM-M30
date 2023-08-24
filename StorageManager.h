#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QStorageInfo>

class StorageManager
{
public:
    StorageManager();
    float GetSDAvailable();
    float GetSDTotal();
    float GeteMMCAvailable();
    float GeteMMCTotal();

    QString GetSDCARDPath();
    QString GetEMMCPath();
    QString GetUSBPath();

private:
    QStorageInfo m_sdStorage;
    QStorageInfo m_emmcStorage;
    QStorageInfo m_usbStorage;
public:
    bool isExistSdcard = false;
    bool isExistEMMccard = false;
    bool isExistUSB = false;

};

#endif // STORAGEMANAGER_H
