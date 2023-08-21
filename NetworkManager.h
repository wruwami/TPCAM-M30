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
    void SetWifiSSidnPW(QString, QString);
    QString getMacAddress(QString);
    QString getMacAddress();

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
