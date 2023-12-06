/**
 * @file NetworkManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief 네트워크를 상태 체크 및 활성화 여부를 관리하는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QJsonObject>
#include <QNetworkInterface>

class NetworkManager
{
public:
    NetworkManager();
//    NetworkManager(QString ssid, QString pw);
    ~NetworkManager();
    void SetNetworkSetting();
//    void SetWifiSSidnPW(QString, QString);
    QString getHardwareAddress(QString);
    QString getWlanAdapterName();
    QString getLanAdapterName();
    bool getNetworkState(QString);
    bool getNetworkUpDown(QString);
    bool getNetworkRunningOrNot(QString);
    QString GetSubNetMask(QString submask);

private:
    void SetWifiStaMode();
    void SetWifiAPMode();
    void SetEtherNet();

private:
    QJsonObject m_wifi_jsonObject;
    QJsonObject m_eth_jsonObject;
    QString m_strNetPlan;
};

#endif // NETWORKMANAGER_H
