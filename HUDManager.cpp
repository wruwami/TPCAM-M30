#include "HUDManager.h"

#include "SpeedUnitManager.h"
#include "ConfigManager.h"

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

void HUDManager::SetDistanceUnit()
{
    if (distance() == meter)
        m_hud.writeNumberToFile("distance_sensitivity_unit", 2);
    else if (distance() == feet)
        m_hud.writeNumberToFile("distance_sensitivity_unit", 3);
}

void HUDManager::SetSpeedUnit()
{
    if (speedUnit() == Km)
    {
        m_hud.writeNumberToFile("speed_unit", 0);
    }
    else if (speedUnit() == mile)
    {
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

void HUDManager::HUDEnforcementInit()
{
    m_hud.writeNumberToFile("display", 1);
    m_hud.writeNumberToFile("clear_content", 1);

    QJsonObject object = ConfigManager("parameter_setting3.json").GetConfig();
    int contrast = 0;
    switch (object["lcd brightness selection"].toInt())
    {
    case 1:
    {
        contrast = 20;
    }
        break;
    case 2:
    {
        contrast = 150;
    }
        break;
    case 3:
    {
        contrast = 255;
    }
        break;
    }


    m_hud.writeNumberToFile("contrast_control", contrast);

    m_hud.writeNumberToFile("pointer", 1);

    ConfigManager config = ConfigManager("parameter_setting2.json");
    object = config.GetConfig();
    switch (object["reticle selection"].toInt())
    {
    case 1:
    {
        SetReticleShape(Dot);
    }
        break;
    case 2:
    {
        SetReticleShape(Cross);
    }
        break;
    case 3:
    {
        SetReticleShape(Round);
    }
        break;
    case 4:
    {
        SetReticleShape(Rectangle);
    }
        break;
    }

    object = ConfigManager("setting_reticle.json").GetConfig();
    m_hud.writeNumberToFile("pointer_x", object["HUD reticle pos"].toArray()[0].toInt());
    m_hud.writeNumberToFile("pointer_y", object["HUD reticle pos"].toArray()[1].toInt());

    SetDistanceUnit();
    m_hud.writeNumberToFile("distance_sensitivity", 0);
    m_hud.writeNumberToFile("distance", 1);

    SetSpeedUnit();
    m_hud.writeNumberToFile("speed", 1);
}

void HUDManager::HUDAlignInit()
{
    m_hud.writeNumberToFile("display", 1);
    m_hud.writeNumberToFile("clear_content", 1);

    QJsonObject object = ConfigManager("parameter_setting3.json").GetConfig();
    int contrast = 0;
    switch (object["lcd brightness selection"].toInt())
    {
    case 1:
    {
        contrast = 20;
    }
        break;
    case 2:
    {
        contrast = 150;
    }
        break;
    case 3:
    {
        contrast = 255;
    }
        break;
    }


    m_hud.writeNumberToFile("contrast_control", contrast);

    m_hud.writeNumberToFile("pointer", 1);

    ConfigManager config = ConfigManager("parameter_setting2.json");
    object = config.GetConfig();
    switch (object["reticle selection"].toInt())
    {
    case 1:
    {
        SetReticleShape(Dot);
    }
        break;
    case 2:
    {
        SetReticleShape(Cross);
    }
        break;
    case 3:
    {
        SetReticleShape(Round);
    }
        break;
    case 4:
    {
        SetReticleShape(Rectangle);
    }
        break;
    }

    object = ConfigManager("setting_reticle.json").GetConfig();
    m_hud.writeNumberToFile("pointer_x", object["HUD reticle pos"].toArray()[0].toInt());
    m_hud.writeNumberToFile("pointer_y", object["HUD reticle pos"].toArray()[1].toInt());

    SetDistanceUnit();
    m_hud.writeNumberToFile("distance_sensitivity", 1);
    m_hud.writeNumberToFile("distance", 0);

//    SetSpeedUnit();
    m_hud.writeNumberToFile("speed", 0);

}

void HUDManager::HUDZoomFocusInit()
{
    m_hud.writeNumberToFile("display", 1);
    m_hud.writeNumberToFile("clear_content", 1);

    QJsonObject object = ConfigManager("parameter_setting3.json").GetConfig();
    int contrast = 0;
    switch (object["lcd brightness selection"].toInt())
    {
    case 1:
    {
        contrast = 20;
    }
        break;
    case 2:
    {
        contrast = 150;
    }
        break;
    case 3:
    {
        contrast = 255;
    }
        break;
    }


    m_hud.writeNumberToFile("contrast_control", contrast);

    m_hud.writeNumberToFile("pointer", 1);

    ConfigManager config = ConfigManager("parameter_setting2.json");
    object = config.GetConfig();
    switch (object["reticle selection"].toInt())
    {
    case 1:
    {
        SetReticleShape(Dot);
    }
        break;
    case 2:
    {
        SetReticleShape(Cross);
    }
        break;
    case 3:
    {
        SetReticleShape(Round);
    }
        break;
    case 4:
    {
        SetReticleShape(Rectangle);
    }
        break;
    }

    object = ConfigManager("setting_reticle.json").GetConfig();
    m_hud.writeNumberToFile("pointer_x", object["HUD reticle pos"].toArray()[0].toInt());
    m_hud.writeNumberToFile("pointer_y", object["HUD reticle pos"].toArray()[1].toInt());

    SetDistanceUnit();
    m_hud.writeNumberToFile("distance_sensitivity", 0);
    m_hud.writeNumberToFile("distance", 1);

//    SetSpeedUnit();
    m_hud.writeNumberToFile("speed", 0);
}

void HUDManager::HUDClear()
{
    m_hud.writeNumberToFile("display", 0) ;
}

CHeadUpDisplay &HUDManager::hud()
{
    return m_hud;
}
