#ifndef SDCARDMANAGER_H
#define SDCARDMANAGER_H

#include <QStorageInfo>

class SdcardManager
{
public:
    SdcardManager();
    int GetSDAvailable();
    int GetSDTotal();
    int GeteMMCAvailable();
    int GeteMMCTotal();

private:
    QStorageInfo m_sdStorage;
    QStorageInfo m_emmcStorage;
public:
    bool isExistSdcard = false;
    bool isExistEMMccard = false;

};

#endif // SDCARDMANAGER_H
