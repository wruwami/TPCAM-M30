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
    void SetDistanceUnit();
    void ShowSpeedUnit(bool);
    void SetPointX(int);
    void SetPointY(int);
    void HUDInit();
    void HUDClear();
    CHeadUpDisplay &hud();

private:
    CHeadUpDisplay m_hud;
};

#endif // HUDMANAGER_H
