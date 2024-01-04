/**
 * @file HUDManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief CHeadUpDisplay를 wrapping 해서 HUD를 쓰기 편하게 만든 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

/**
 * @brief CHeadUpDisplay를 wrapping 해서 HUD를 쓰기 편하게 만든 클래스
 * 
 */
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
    void HUDAlignInit(bool);
    void HUDZoomFocusInit();
    void HUDClear();
    void HUDEnforcement(bool, float, float);
    void HUDEnforcementDistance(bool, float, float);
    void HUDEnforcementLimitOver(float, float);
    void HUDEnforcementSpeedClear();
    void HUDEnforcementDistanceClear();
    void HUDAlign(float, int);
    void HUDAlignClear();
    void HUDZoomFocus(float);
    void HUDZoomFocusClear();

    CHeadUpDisplay &hud();

private:
    CHeadUpDisplay m_hud;
};

#endif // HUDMANAGER_H
