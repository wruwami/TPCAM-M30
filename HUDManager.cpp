#include "HUDManager.h"

#include "SpeedUnitManager.h"

HUDManager::HUDManager()
{

}

// 0 Dot,
// 1 Cross,
// 2 Round,
// 3 Rectangle
void HUDManager::SetReticleShape(Shape shape)
{
    m_hud.writeNumberToFile("pointer_shape", shape);
}

void HUDManager::ShowSpeed(bool nSpeed, bool nRec)
{
    if (nRec)
        m_hud.writeNumberToFile("speed", 2);
    else if (nSpeed)
        m_hud.writeNumberToFile("speed", 1);
    else
        m_hud.writeNumberToFile("speed", 0);
}

void HUDManager::ShowDistance(bool nShow)
{
    if (nShow)
        m_hud.writeNumberToFile("distance", 1);
    else
        m_hud.writeNumberToFile("distance", 0);
}

void HUDManager::ShowDistanceUnit(bool nShow)
{
    if (nShow && distance() == meter)
        m_hud.writeNumberToFile("distance_sensitivity_unit", 2);
    else if (!nShow && distance() == meter)
        m_hud.writeNumberToFile("distance_sensitivity_unit", 0);
    else if (nShow && distance() == feet)
        m_hud.writeNumberToFile("distance_sensitivity_unit", 3);
    else if (!nShow && distance() == feet)
        m_hud.writeNumberToFile("distance_sensitivity_unit", 1);
}

void HUDManager::ShowSpeedUnit(bool nShow)
{
    if (!nShow)
        m_hud.writeNumberToFile("speed", 0);
    else if (speedUnit() == Km)
    {
        m_hud.writeNumberToFile("speed", 1);
        m_hud.writeNumberToFile("speed_unit", 0);
    }
    else if (speedUnit() == mile)
    {
        m_hud.writeNumberToFile("speed", 1);
        m_hud.writeNumberToFile("speed_unit", 1);
    }
}

void HUDManager::SetPointX(int value)
{
    m_hud.writeNumberToFile("pointer_x", value);
}

void HUDManager::SetPointY(int value)
{
    m_hud.writeNumberToFile("pointer_y", value);
}

void HUDManager::HUDInit()
{
    m_hud.writeNumberToFile("clear_content", 1);
}

CHeadUpDisplay &HUDManager::hud()
{
    return m_hud;
}
