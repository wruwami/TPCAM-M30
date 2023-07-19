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

private:
    Distance m_distance = meter;
    SpeedUnit m_speedUnit = Km;
};

static QString distance()
{
    return SpeedUnitManager::GetInstance()->distance();
}

static void setDistance(Distance newDistance)
{
    SpeedUnitManager::GetInstance()->setDistance(newDistance);
}

static QString speedUnit()
{
    return SpeedUnitManager::GetInstance()->speedUnit();
}

static void setSpeedUnit(SpeedUnit newSpeedUnit)
{
    SpeedUnitManager::GetInstance()->setSpeedUnit(newSpeedUnit);
}

static Distance distanceValue()
{
    return SpeedUnitManager::GetInstance()->distanceValue();
}

static SpeedUnit speedUnitValue()
{
    return SpeedUnitManager::GetInstance()->speedUnitValue();
}


#endif // SPEEDUNITMANAGER_H
