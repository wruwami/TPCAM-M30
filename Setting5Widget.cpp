#include "Setting5Widget.h"
#include "ui_Setting5Widget.h"

#include <QSpacerItem>
#include <QJsonArray>

#include "StringLoader.h"
#include "NetworkManager.h"

Setting5Widget::Setting5Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting5Widget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;


    ui->ipAddressLabel->setText(LoadString("IDS_IP_ADDRESS"));
    ui->ipAddressLabel->setFontSize(23);

//    ui->ipAddressComboBox->addItem(LoadString("IDS_DHCP"));
//    ui->ipAddressComboBox->addItem(LoadString("IDS_MANUAL"));
//    ui->ipAddressComboBox->setCurrentIndex(0);
    foreach (QJsonValue json, m_jsonObject["ethernet_mode items"].toArray())
    {
        ui->ipAddressComboBox->addItem(LoadString(json.toString().toStdString()));
    }

    int index = m_jsonObject["ethernet_mode select"].toInt();
    ui->ipAddressComboBox->setCurrentIndex(index - 1);

    ui->ipLineEdit->SetMode(Mode::KeypadType);
    ui->subnetMaskLineEdit->SetMode(Mode::KeypadType);
    ui->gatewayLineEdit->SetMode(Mode::KeypadType);
    ui->dnsServerLineEdit->SetMode(Mode::KeypadType);

    //disable when ethernet is not connected
    NetworkManager networkManager;
    if (!networkManager.getNetworkRunningOrNot(networkManager.getLanAdapterName()))
    {
        ui->ipAddressComboBox->setEnabled(false);
        ui->ipLineEdit->setEnabled(false);
        ui->subnetMaskLineEdit->setEnabled(false);
        ui->gatewayLineEdit->setEnabled(false);
        ui->dnsServerLineEdit->setEnabled(false);

        ui->ipAddressLabel->setEnabled(false);
        ui->IpLabel->setEnabled(false);
        ui->subnetMaskLabel->setEnabled(false);
        ui->gatewayLabel->setEnabled(false);
        ui->dnsServerLabel->setEnabled(false);
    }

    startTimer(3000);
}

Setting5Widget::~Setting5Widget()
{
    delete ui;
}

void Setting5Widget::SaveConfig()
{
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

}

void Setting5Widget::setDHCPMode()
{
    ui->IpLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->IpLabel->setFontSize(23);
    ui->ipLineEdit->setDisabled(true);
    NetworkManager networkManager;
    ui->ipLineEdit->setText(networkManager.getHardwareAddress(networkManager.getLanAdapterName()));
    ui->gatewayLabel->hide();
    ui->subnetMaskLabel->hide();
    ui->dnsServerLabel->hide();
    ui->subnetMaskLineEdit->hide();
    ui->gatewayLineEdit->hide();
    ui->dnsServerLineEdit->hide();
    ui->gridLayout->addItem(new QSpacerItem(ui->subnetMaskLineEdit->size().width(), ui->subnetMaskLineEdit->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 1);
    ui->gridLayout->addItem(new QSpacerItem(ui->gatewayLineEdit->size().width(), ui->gatewayLineEdit->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 6, 1);
    ui->gridLayout->addItem(new QSpacerItem(ui->dnsServerLineEdit->size().width(), ui->dnsServerLineEdit->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 1);

    m_newJsonObject["mac address"] = networkManager.getHardwareAddress(networkManager.getLanAdapterName());
//    ui->ipLineEdit->setText(m_jsonObject["mac address"].toString());
}

void Setting5Widget::setManualMode()
{
    if ( ui->gridLayout->rowCount() > 6)
    {
        ui->gridLayout->removeItem(ui->gridLayout->itemAtPosition(5, 1));
        ui->gridLayout->removeItem(ui->gridLayout->itemAtPosition(6, 1));
        ui->gridLayout->removeItem(ui->gridLayout->itemAtPosition(7, 1));

//        delete ui->gridLayout->itemAtPosition(5, 1)->widget();
//        delete ui->gridLayout->itemAtPosition(6, 1)->widget();
//        delete ui->gridLayout->itemAtPosition(7, 1)->widget();
    }
    ui->ipLineEdit->setDisabled(false);
    ui->ipLineEdit->clear();
    ui->gatewayLabel->show();
    ui->subnetMaskLabel->show();
    ui->dnsServerLabel->show();
    ui->subnetMaskLineEdit->show();
    ui->gatewayLineEdit->show();
    ui->dnsServerLineEdit->show();
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->IpLabel->setFontSize(23);
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));
    ui->gatewayLabel->setFontSize(23);
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->subnetMaskLabel->setFontSize(23);
    ui->dnsServerLabel->setText(LoadString("IDS_DNS_SERVER"));
    ui->dnsServerLabel->setFontSize(23);

    ui->ipLineEdit->setText(m_jsonObject["ip"].toString());
    ui->subnetMaskLineEdit->setText(m_jsonObject["subnet mask"].toString());
    ui->gatewayLineEdit->setText(m_jsonObject["gateway"].toString());
    ui->dnsServerLineEdit->setText(m_jsonObject["dns server"].toString());

}

void Setting5Widget::on_ipAddressComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["ethernet_mode select"] = index + 1;
    switch (index)
    {
    case 0:
    {
        setManualMode();
    }
        break;
    case 1:
    {
        setDHCPMode();
    }
        break;
    }
}


void Setting5Widget::on_ipLineEdit_textChanged(const QString &arg1)
{
    int index = m_newJsonObject["ethernet_mode select"].toInt();
    switch (index)
    {
    case 1:
    {
        m_newJsonObject["ip"] = arg1;
    }
        break;
    case 2:
    {
        m_newJsonObject["mac address"] = arg1;
    }
        break;
    }
}

void Setting5Widget::on_subnetMaskLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["subnet mask"] = arg1;
}

void Setting5Widget::on_gatewayLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["gateway"] = arg1;
}

void Setting5Widget::on_dnsServerLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["dns server"] = arg1;
}

void Setting5Widget::timerEvent(QTimerEvent *event)
{
    //disable when ethernet is not connected
    NetworkManager networkManager;
    if (!networkManager.getNetworkRunningOrNot(networkManager.getLanAdapterName()))
    {
        ui->ipAddressComboBox->setEnabled(false);
        ui->ipLineEdit->setEnabled(false);
        ui->subnetMaskLineEdit->setEnabled(false);
        ui->gatewayLineEdit->setEnabled(false);
        ui->dnsServerLineEdit->setEnabled(false);

        ui->ipAddressLabel->setEnabled(false);
        ui->IpLabel->setEnabled(false);
        ui->subnetMaskLabel->setEnabled(false);
        ui->gatewayLabel->setEnabled(false);
        ui->dnsServerLabel->setEnabled(false);
    }
    else
    {
        ui->ipAddressComboBox->setEnabled(true);
//        ui->ipLineEdit->setEnabled(true);
        ui->subnetMaskLineEdit->setEnabled(true);
        ui->gatewayLineEdit->setEnabled(true);
        ui->dnsServerLineEdit->setEnabled(true);

        ui->ipAddressLabel->setEnabled(true);
        ui->IpLabel->setEnabled(true);
        ui->subnetMaskLabel->setEnabled(true);
        ui->gatewayLabel->setEnabled(true);
        ui->dnsServerLabel->setEnabled(true);
    }
}
