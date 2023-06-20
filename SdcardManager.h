#ifndef SDCARDMANAGER_H
#define SDCARDMANAGER_H

#include <QStorageInfo>

class SdcardManager
{
public:
    SdcardManager();
    float GetSDAvailable();
    float GetSDTotal();
    float GeteMMCAvailable();
    float GeteMMCTotal();

private:
    QStorageInfo m_sdStorage;
    QStorageInfo m_emmcStorage;
public:
    bool isExistSdcard = false;
    bool isExistEMMccard = false;

};

#endif // SDCARDMANAGER_H
