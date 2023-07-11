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
