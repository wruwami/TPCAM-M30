/**
 * @file LightManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief light를 기능시키는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H


class LightManager
{
public:
    LightManager();
    void SwapLight();
private:
    bool isLightOn = true;
};

#endif // LIGHTMANAGER_H
