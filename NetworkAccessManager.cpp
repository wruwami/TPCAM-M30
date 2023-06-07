#include "NetworkAccessManager.h"

#include <QNetworkConfigurationManager>

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    : QObject{parent}
{

}

QStringList NetworkAccessManager::findActiveWirelesses()
{
    QNetworkConfigurationManager ncm;
    netcfgList = ncm.allConfigurations();
    WiFisList.clear();
    for (auto &x : netcfgList)
    {
        if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
        {
            if(x.name() == "")
                WiFisList << "Unknown(Other Network)";
            else
                WiFisList << x.name();

//            qDebug() << x.type();
        }
    }
    return WiFisList;
}
