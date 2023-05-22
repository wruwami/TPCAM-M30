#ifndef SDCARDMANAGER_H
#define SDCARDMANAGER_H

#include <QStorageInfo>

class SdcardManager
{
public:
    SdcardManager();
    int GetAvailable();
    int GetTotal();
private:
    QStorageInfo m_storage;

};

#endif // SDCARDMANAGER_H
