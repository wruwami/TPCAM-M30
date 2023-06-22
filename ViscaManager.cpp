#include "ViscaManager.h"

#include <QDebug>
#include <QJsonObject>

#include "ConfigManager.h"

ViscaManager::ViscaManager()
{
    if (m_serialViscaManager.connectVisca() != "Connect")
    {
        qDebug() << "serial not connected";
        return;
    }
}

ViscaManager::~ViscaManager()
{
    m_serialViscaManager.close();
}

void ViscaManager::SetDayMode(QJsonObject object)
{
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void ViscaManager::SetDayMode(int index)
{
    ConfigManager config = ConfigManager("exposure.json");
    QJsonObject object = config.GetConfig();
    QJsonObject ret;
    switch (index) {
    case 1:
    {
        ret = object["Day"].toObject()["Dark"].toObject();
    }
        break;
    case 2:
    {
        ret = object["Day"].toObject()["Normal"].toObject();
    }
        break;
    case 3:
    {
        ret = object["Day"].toObject()["Bright"].toObject();
    }
        break;
    case 4:
    {
        ret = object["Night"].toObject()["Dark"].toObject();
    }
        break;
    case 5:
    {
        ret = object["Night"].toObject()["Normal"].toObject();
    }
        break;
    case 6:
    {
        ret = object["Night"].toObject()["Bright"].toObject();
    }
        break;
    }
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(ret["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(ret["Shutter"].toInt());
    m_serialViscaManager.set_gain(ret["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    ret["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    ret["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    ret["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();

}
