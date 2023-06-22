#ifndef LASERMANAGER_H
#define LASERMANAGER_H

#include "SerialLaserManager.h"
#include <QJsonObject>

class LaserManager
{
public:
    LaserManager();
    virtual ~LaserManager();
    void SetWeatherMode(int);
private:
    SerialLaserManager m_serialLaserManager;
};

#endif // LASERMANAGER_H
