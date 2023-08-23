#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QJsonObject>
#include <QNetworkInterface>

class NetworkManager
{
public:
    NetworkManager();
    NetworkManager(QString ssid, QString pw);
    ~NetworkManager();
    void SetNetworkSetting();
//    void SetWifiSSidnPW(QString, QString);
    QString getHardwareAddress(QString);
    QString getWlanAdapterName();
    QString getLanAdapterName();

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
