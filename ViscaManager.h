#ifndef VISCAMANAGER_H
#define VISCAMANAGER_H

#include "SerialViscaManager.h"
#include "QJsonObject"

class ViscaManager
{
public:
    ViscaManager();
    virtual ~ViscaManager();
    void SetDayMode(QJsonObject);
    void SetDayMode(int);
private:
    SerialViscaManager m_serialViscaManager;
};

#endif // VISCAMANAGER_H
