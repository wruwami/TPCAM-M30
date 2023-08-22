#include "NetworkAccessManager.h"

#include <QNetworkConfigurationManager>
#include <QDebug>

#include "NetworkManager.h"
#include "wifi_scan.h"

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    : QObject{parent}
{

}

QStringList NetworkAccessManager::findActiveWirelesses()
{
//    QNetworkConfigurationManager ncm;
//    netcfgList = ncm.allConfigurations();
    WiFisList.clear();
//    for (auto &x : netcfgList)
//    {
//        if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
//        {
//            if(x.name() == "")
//                WiFisList << "Unknown(Other Network)";
//            else
//                WiFisList << x.name();

////            qDebug() << x.type();
//        }
//    }
    NetworkManager networkManager;

    int status, i;
    struct bss_info bss[10];
    struct wifi_scan *wifi = wifi_scan_init(networkManager.getWlanAdapterName().toStdString().c_str());

    status=wifi_scan_all(wifi, bss, 10);
    for(i=0;i<status && i<10;++i)
    {
        if (!QString(bss[i].ssid).isEmpty())
            WiFisList.append(QString(bss[i].ssid));
//        sprintf(tmp, "%s signal %d dBm on %u MHz seen %d ms ago status %s\n",
//        bss[i].signal_mbm/100, bss[i].frequency, bss[i].seen_ms_ago,
//        (bss[i].status==BSS_ASSOCIATED ? "associated" : ""));
//        qDebug() << tmp;
    }
    wifi_scan_close(wifi);
    return WiFisList;
}
