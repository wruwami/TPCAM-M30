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

    bool GetSDExitSelfTest();
    bool GetSDExitEnforcement();
    bool GetEMMCExitSelfTest();

private:
    QStorageInfo m_sdStorage;
    QStorageInfo m_emmcStorage;
    QStorageInfo m_usbStorage;
    double m_fEMMCExitSelfTestPercent;
    double m_fSDExitSelfTestPercent;
    double m_fSDExitEnforcementPercent;
public:
    bool isExistSdcard = false;
    bool isExistEMMccard = false;
    bool isExistUSB = false;

};

#endif // STORAGEMANAGER_H
