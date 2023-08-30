#include "NetworkManager.h"

#include <QFile>
#include <QTextStream>
#include <QNetworkInterface>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <ifaddrs.h>

#include "ConfigManager.h"

#define NET_PATH   /etc/netplan/000-default.yaml
#define ETH_ADAPTER     "eth0"
#define BUFF_SIZE 1024

NetworkManager::NetworkManager()
{
    ConfigManager wifi_config = ConfigManager("parameter_setting4.json");
    m_wifi_jsonObject = wifi_config.GetConfig();

    ConfigManager eth_config = ConfigManager("parameter_setting5.json");
    m_eth_jsonObject = eth_config.GetConfig();

    bool bEnableWifi = false;
    if (ConfigManager("parameter_setting5.json").GetConfig()["wifi select"].toInt() == 1)
        bEnableWifi = true;

    m_strNetPlan = "network: \n\
    version: 2 \n\
    renderer: NetworkManager\n";

    SetEtherNet();

    if (bEnableWifi)
    {
        if(m_wifi_jsonObject["wifi_mode"].toString() == "STA")
        {
            SetWifiStaMode();
        }
        else
        {
            SetWifiAPMode();
        }
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

//void NetworkManager::SetWifiSSidnPW(QString ssid, QString pw)
//{
//    QString gateway = m_wifi_jsonObject["ip"].toString();
//    QStringList stringList = gateway.split(".");
//    gateway = stringList[0] + "." + stringList[1] + "." + stringList[2] + "." + "1";

//    m_strNetPlan.append(QString("    wifis: \n\
//       wlx200db01ff154: \n\
//          dhcp4: no \n\
//          gateway4: %1 \n\
//          addresses: [%2/%3] \n\
//          access-points: \n\
//             \"%4\": \n\
//             password: \"%5\" \n\
//                        ").arg(gateway).arg(m_wifi_jsonObject["ip"].toString()).arg(GetSubNetMask(m_wifi_jsonObject["subnet mask"].toString())).arg(ssid).arg(pw));
//}

QString NetworkManager::getHardwareAddress(QString deviceName)
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            if (netInterface.name() == deviceName)
                return netInterface.hardwareAddress();
    }
    return QString();
}

QString NetworkManager::getWlanAdapterName()
{

//    struct ifaddrs *addrs;
//     getifaddrs(&addrs);

//     for (struct ifaddrs *addr = addrs; addr != nullptr; addr = addr->ifa_next) {
//         if (addr->ifa_addr && addr->ifa_addr->sa_family == AF_PACKET) {
//             qDebug() << addr->ifa_name;
//         }
//     }

    QString strWlan;
    char  buff[BUFF_SIZE];
    FILE *fp;

    fp = popen("iwconfig | grep WIFI | awk '{print $1}'", "r");
    if (NULL == fp)
    {
        perror("popen() 실패");
        return "";
    }

    while (fgets(buff, BUFF_SIZE, fp))
        printf("%s", buff);

    QString ret(buff);
    QStringList retList = ret.split("\n");
    foreach (auto item, retList)
    {
        if (!item.contains("no wireless extensions.") && !item.isEmpty())
        {
            strWlan = item;
            break;
        }
    }

    pclose(fp);

    return strWlan;




//     freeifaddrs(addrs);
//    QStringList networkInterfaceList;
//    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
//    {
//        // Return only the first non-loopback MAC Address
//        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
//        {
//            networkInterfaceList.append(netInterface.name());
//        }
//    }

//    QNetworkConfigurationManager ncm;
//    QList<QNetworkConfiguration> netcfg = ncm.allConfigurations();

//    QNetworkConfiguration networkConfiguration;
//    foreach (auto item, networkConfiguration.children())
//    {
//        if (networkInterfaceList.contains(item.name()))
//        {
//            if (item.bearerType() == QNetworkConfiguration::BearerWLAN)
//                return item.name();
//        }
//    }

    //    return QString();
}

QString NetworkManager::getLanAdapterName()
{
    return QString(ETH_ADAPTER);
}

void NetworkManager::SetWifiStaMode()
{
    QString gateway = m_wifi_jsonObject["ip"].toString();
    QStringList stringList = gateway.split(".");
    gateway = stringList[0] + "." + stringList[1] + "." + stringList[2] + "." + "1";
    QString ssid = m_wifi_jsonObject["sta ssid"].toArray()[0].toString();

    m_strNetPlan.append(QString("    wifis: \n\
       %1: \n\
          dhcp4: no \n\
          gateway4: %2 \n\
          addresses: [%3/%4] \n\
          access-points: \n\
             \"%5\": \n\
                password: \"%6\" \n\
").arg(getWlanAdapterName()).arg(gateway).arg(m_wifi_jsonObject["ip"].toString()).arg(GetSubNetMask(m_wifi_jsonObject["subnet mask"].toString())).arg(ssid).arg(m_wifi_jsonObject["sta ftp id & p/w"].toString()));
}

void NetworkManager::SetWifiAPMode()
{
    QString gateway = m_wifi_jsonObject["ip"].toString();
    QStringList stringList = gateway.split(".");
    gateway = stringList[0] + "." + stringList[1] + "." + stringList[2] + "." + "1";

    m_strNetPlan.append(QString("    wifis: \n\
       %1: \n\
          dhcp4: no \n\
          gateway4: %1 \n\
          addresses: [%2/%3] \n\
          access-points: \n\
             \"%4\": \n\
                password: \"%5\" \n\
                mode: ap \
").arg(getWlanAdapterName()).arg(gateway).arg(m_wifi_jsonObject["ip"].toString()).arg(GetSubNetMask(m_wifi_jsonObject["subnet mask"].toString())).arg(m_wifi_jsonObject["sta ssid"].toString()).arg(m_wifi_jsonObject["sta ftp id & p/w"].toString()));
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

