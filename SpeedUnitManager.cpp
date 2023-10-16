#include "SpeedUnitManager.h"

#include "ConfigManager.h"

SpeedUnitManager* SpeedUnitManager::instance = nullptr;

SpeedUnitManager::SpeedUnitManager()
{
    ConfigManager config = ConfigManager("parameter_setting3.json");
    QJsonObject object = config.GetConfig();
    if (object["unit selection"].toInt() == 1)
    {
        m_distance = meter;
        m_speedUnit = Km;
    }
    else
    {
        m_distance = feet;
        m_speedUnit = mile;
    }
}

QString SpeedUnitManager::distance()
{
    if (m_distance == meter)
        return "m";
    return "ft";
}

Distance SpeedUnitManager::distanceValue()
{
    return m_distance;
}

void SpeedUnitManager::setDistance(Distance newDistance)
{
    m_distance = newDistance;
}

SpeedUnit SpeedUnitManager::speedUnitValue()
{
    return m_speedUnit;
}

QString SpeedUnitManager::speedUnit()
{
    if (m_speedUnit == Km)
        return "km/h";
    return "mph";
}

void SpeedUnitManager::setSpeedUnit(SpeedUnit newSpeedUnit)
{
    m_speedUnit = newSpeedUnit;
}

float SpeedUnitManager::getSpeedValue(float Kmh)
{
    if (m_speedUnit == Km)
        return Kmh;
    return Kmh * 0.621;
}

float SpeedUnitManager::getDistanceValue(float meter)
{
    if (m_distance == Distance::meter)
        return meter;
    return meter * 3.28;
}
