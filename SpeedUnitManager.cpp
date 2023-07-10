#include "SpeedUnitManager.h"

SpeedUnitManager* SpeedUnitManager::instance = nullptr;

QString SpeedUnitManager::distance() const
{
    if (m_distance == meter)
        return "m";
    return "ft";
}

void SpeedUnitManager::setDistance(Distance newDistance)
{
    m_distance = newDistance;
}

QString SpeedUnitManager::speedUnit() const
{
    if (m_speedUnit == Km)
        return "km/h";
    return "mph";
}

void SpeedUnitManager::setSpeedUnit(SpeedUnit newSpeedUnit)
{
    m_speedUnit = newSpeedUnit;
}
