#include "LaserManager.h"

#include <QDebug>

LaserManager::LaserManager()
{
    if (m_serialLaserManager.connectLaser() != "Connect")
    {
        qDebug() << "serial not connected ";
        return;
    }
}

LaserManager::~LaserManager()
{
    m_serialLaserManager.close();
}

void LaserManager::SetWeatherMode(int index)
{
    m_serialLaserManager.set_weather_mode(index);
}
