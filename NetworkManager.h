#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QJsonObject>

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();
    void SetNetworkSetting();
private:
    void SetWifiStaMode();
    void SetWifiAPMode();
    void SetEtherNet();
    QString GetSubNetMask(QString submask);
private:
    QJsonObject m_wifi_jsonObject;
    QJsonObject m_eth_jsonObject;
    QString m_strNetPlan;
};

#endif // NETWORKMANAGER_H
