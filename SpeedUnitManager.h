/**
 * @file SpeedUnitManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief 속도 거리 단위 설정 관리 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SPEEDUNITMANAGER_H
#define SPEEDUNITMANAGER_H

#include <QString>

enum Distance{
    meter,
    feet,
};

enum SpeedUnit{
    Km,
    mile,
};

/**
 * @brief 속도 거리 단위 설정 관리 클래스
 * 
 */
class SpeedUnitManager
{
    SpeedUnitManager();
    SpeedUnitManager(const SpeedUnitManager& other);
    ~SpeedUnitManager() {}
    static SpeedUnitManager* instance;
public:
    static SpeedUnitManager* GetInstance()
    {
        if(instance == nullptr) instance = new SpeedUnitManager();
        return instance;
    }

    QString distance();
    Distance distanceValue();
    void setDistance(Distance newDistance);

    SpeedUnit speedUnitValue();
    QString speedUnit();
    void setSpeedUnit(SpeedUnit newSpeedUnit);
    float getSpeedValue(float);
    float getDistanceValue(float);

private:
    Distance m_distance = meter;
    SpeedUnit m_speedUnit = Km;
};

static QString distanceValue()
{
    return SpeedUnitManager::GetInstance()->distance();
}

static void setDistance(Distance newDistance)
{
    SpeedUnitManager::GetInstance()->setDistance(newDistance);
}

static QString speedUnitValue()
{
    return SpeedUnitManager::GetInstance()->speedUnit();
}

static void setSpeedUnit(SpeedUnit newSpeedUnit)
{
    SpeedUnitManager::GetInstance()->setSpeedUnit(newSpeedUnit);
}

static Distance distance()
{
    return SpeedUnitManager::GetInstance()->distanceValue();
}

static SpeedUnit speedUnit()
{
    return SpeedUnitManager::GetInstance()->speedUnitValue();
}

static float getSpeedValue(float Kmh)
{
    return SpeedUnitManager::GetInstance()->getSpeedValue(Kmh);
}
static float getDistanceValue(float meter)
{
    return SpeedUnitManager::GetInstance()->getDistanceValue(meter);
}


#endif // SPEEDUNITMANAGER_H
