#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QJsonObject>

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    void SetWifiStaMode();
    void SetWifiAPMode();
    void SetEtherNet();
private:
    QJsonObject m_wifi_jsonObject;
    QJsonObject m_eth_jsonObject;
};

#endif // NETWORKMANAGER_H
