#include "NetworkManager.h"

#include "ConfigManager.h"

#define WIFI_PATH   /etc/netplan/000-wifis.yaml
#define ETH_PATH   /etc/netplan/000-default.yaml
#define WIFI_ADAPTER    wlx200db01ff154
#define ETH_ADAPTER     eth0

NetworkManager::NetworkManager()
{
    ConfigManager wifi_config = ConfigManager("parameter_setting4.json");
    m_wifi_jsonObject = wifi_config.GetConfig();

    ConfigManager eth_config = ConfigManager("parameter_setting5.json");
    m_eth_jsonObject = eth_config.GetConfig();

}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::SetWifiStaMode()
{

}

void NetworkManager::SetWifiAPMode()
{

}

void NetworkManager::SetEtherNet()
{

}

