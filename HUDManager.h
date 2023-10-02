#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include "HeadUpDisplay.h"


enum Shape
{
    Dot = 0,
    Cross = 1,
    Round = 2,
    Rectangle = 3,

};

class HUDManager
{
public:
    HUDManager();
    void SetReticleShape(Shape);
    void ShowSpeed(bool, bool);
    void ShowDistance(bool);
    void ShowDistanceUnit(bool);
    void SetDistanceSensitivityUnit();
    void SetDistanceUnit();
    void SetSpeedUnit();
    void SetPointX(int);
    void SetPointY(int);
    void HUDEnforcementInit();
    void HUDAlignInit();
    void HUDZoomFocusInit();
    void HUDClear();
    void HUDEnforcement(bool, float, float);
    void HUDEnforcementLimitOver(float, float);
    void HUDEnforcementClear();
    void HUDAlign(float, int);
    void HUDAlignClear();
    void HUDZoomFocus(float);
    void HUDZoomFocusClear();

    CHeadUpDisplay &hud();

private:
    CHeadUpDisplay m_hud;
};

#endif // HUDMANAGER_H
