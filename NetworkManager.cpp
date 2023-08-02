#include "NetworkManager.h"

#include <QFile>
#include <QTextStream>
#include <QNetworkInterface>


#include "ConfigManager.h"

#define NET_PATH   /etc/netplan/000-default.yaml
#define WIFI_ADAPTER    wlx200db01ff154
#define ETH_ADAPTER     eth0

NetworkManager::NetworkManager()
{
    ConfigManager wifi_config = ConfigManager("parameter_setting4.json");
    m_wifi_jsonObject = wifi_config.GetConfig();

    ConfigManager eth_config = ConfigManager("parameter_setting5.json");
    m_eth_jsonObject = eth_config.GetConfig();

    m_strNetPlan = "network: \n\
    version: 2 \n\
    renderer: NetworkManager\n";

     SetEtherNet();

    if(m_wifi_jsonObject["wifi_mode"].toString() == "STA")
    {
        SetWifiStaMode();
    }
    else
    {
        SetWifiAPMode();
    }
}

NetworkManager::NetworkManager(QString ssid, QString pw)
{
    ConfigManager wifi_config = ConfigManager("parameter_setting4.json");
    m_wifi_jsonObject = wifi_config.GetConfig();

    ConfigManager eth_config = ConfigManager("parameter_setting5.json");
    m_eth_jsonObject = eth_config.GetConfig();

    m_strNetPlan = "network: \n\
    version: 2 \n\
    renderer: NetworkManager\n";

    SetEtherNet();

    SetWifiStaMode();

}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::SetNetworkSetting()
{
    QFile existFile("/etc/netplan/01-network-manager-all.yaml");
    existFile.open(QFile::ReadOnly);
    if (existFile.exists())
        existFile.remove();

    QFile file("/etc/netplan/01-network-manager-all.yaml");
    file.open(QFile::WriteOnly);
    file.write(m_strNetPlan.toUtf8());
    file.close();

    system("sudo netplan apply");

}

void NetworkManager::SetWifiSSidnPW(QString ssid, QString pw)
{
    QString gateway = m_wifi_jsonObject["ip"].toString();
    QStringList stringList = gateway.split(".");
    gateway = stringList[0] + "." + stringList[1] + "." + stringList[2] + "." + "1";

    m_strNetPlan.append(QString("    wifis: \n\
       wlx200db01ff154: \n\
          dhcp4: no \n\
          gateway4: %1 \n\
          addresses: [%2/%3] \n\
          access-points: \n\
             \"%4\": \n\
             password: \"%5\" \n\
                        ").arg(gateway).arg(m_wifi_jsonObject["ip"].toString()).arg(GetSubNetMask(m_wifi_jsonObject["subnet mask"].toString())).arg(ssid).arg(pw));
}

QString NetworkManager::getMacAddress(QString deviceName)
{

    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            if (netInterface.name() == deviceName)
                return netInterface.hardwareAddress();
    }
    return QString();
}

void NetworkManager::SetWifiStaMode()
{
    QString gateway = m_wifi_jsonObject["ip"].toString();
    QStringList stringList = gateway.split(".");
    gateway = stringList[0] + "." + stringList[1] + "." + stringList[2] + "." + "1";

    m_strNetPlan.append(QString("    wifis: \n\
       wlx200db01ff154: \n\
          dhcp4: no \n\
          gateway4: %1 \n\
          addresses: [%2/%3] \n\
          access-points: \n\
             \"%4\": \n\
             password: \"%5\" \n\
").arg(gateway).arg(m_wifi_jsonObject["ip"].toString()).arg(GetSubNetMask(m_wifi_jsonObject["subnet mask"].toString())).arg(m_wifi_jsonObject["sta ssid"].toString()).arg(m_wifi_jsonObject["sta ftp id & p/w"].toString()));
}

void NetworkManager::SetWifiAPMode()
{
    QString gateway = m_wifi_jsonObject["ip"].toString();
    QStringList stringList = gateway.split(".");
    gateway = stringList[0] + "." + stringList[1] + "." + stringList[2] + "." + "1";

    m_strNetPlan.append(QString("    wifis: \n\
       wlx200db01ff154: \n\
          dhcp4: no \n\
          gateway4: %1 \n\
          addresses: [%2/%3] \n\
          access-points: \n\
             \"%4\": \n\
             password: \"%5\" \n\
             mode: ap \
").arg(gateway).arg(m_wifi_jsonObject["ip"].toString()).arg(GetSubNetMask(m_wifi_jsonObject["subnet mask"].toString())).arg(m_wifi_jsonObject["sta ssid"].toString()).arg(m_wifi_jsonObject["sta ftp id & p/w"].toString()));
}

void NetworkManager::SetEtherNet()
{
    if (m_eth_jsonObject["ethernet_mode select"].toInt() == 1)
    {
        m_strNetPlan.append(QString("    ethernets: \n\
       eth0: \n\
          dhcp4: no \n\
          addresses: [%1/%2] \n\
          gateway4: %3 \n\
          nameservers: \n\
             addresses: [%4] \n").arg(m_eth_jsonObject["ip"].toString()).arg(GetSubNetMask(m_eth_jsonObject["subnet mask"].toString())).arg(m_eth_jsonObject["gateway"].toString()).arg(m_eth_jsonObject["dns server"].toString()));
    }
    else
    {
        m_strNetPlan.append("    ethernets: \n\
       eth0: \n\
          dhcp4: yes \n");
    }
}

QString NetworkManager::GetSubNetMask(QString submask)
{
    if (submask == "255.255.255.0")
    {
        return "24";
    }
    else if (submask == "255.255.0.0")
    {
        return "16";
    }
    else if (submask == "255.0.0.0)")
    {
        return "8";
    }
    return "24";
}

QString getMacAddress()
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            return netInterface.hardwareAddress();
    }
    return QString();
}

