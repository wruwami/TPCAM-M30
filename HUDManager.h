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
    void ShowSpeedUnit(bool);
    void SetPointX(int);
    void SetPointY(int);
    void HUDInit();
    CHeadUpDisplay &hud();

private:
    CHeadUpDisplay m_hud;
};

#endif // HUDMANAGER_H
