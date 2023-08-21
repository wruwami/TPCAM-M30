#include "NetworkAccessManager.h"

#include <QNetworkConfigurationManager>
#include <QDebug>

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
    int status, i;
    struct bss_info bss[10];
    struct wifi_scan *wifi = wifi_scan_init("wlxe0e1a993b0fc");

    status=wifi_scan_all(wifi, bss, 10);
    char* tmp;
    for(i=0;i<status && i<10;++i)
    {
        WiFisList.append(QString(bss[i].ssid));
//        sprintf(tmp, "%s signal %d dBm on %u MHz seen %d ms ago status %s\n",
//        bss[i].signal_mbm/100, bss[i].frequency, bss[i].seen_ms_ago,
//        (bss[i].status==BSS_ASSOCIATED ? "associated" : ""));
//        qDebug() << tmp;
    }
    wifi_scan_close(wifi);
    return WiFisList;
}
