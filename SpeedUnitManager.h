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

    QString distance() const;
    void setDistance(Distance newDistance);

    QString speedUnit() const;
    void setSpeedUnit(SpeedUnit newSpeedUnit);

private:
    Distance m_distance = meter;
    SpeedUnit m_speedUnit = Km;
};

#endif // SPEEDUNITMANAGER_H
