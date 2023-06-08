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
private:
    CHeadUpDisplay m_hud;
};

#endif // HUDMANAGER_H
