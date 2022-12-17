#include "Setting5Widget.h"
#include "ui_Setting5Widget.h"

#include <QSpacerItem>

#include "StringLoader.h"

Setting5Widget::Setting5Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting5Widget)
{
    ui->setupUi(this);

    ui->ipAddressLabel->setText(LoadString("IDS_IP_ADDRESS"));

    ui->ipAddressComboBox->addItem(LoadString("IDS_DHCP"));
    ui->ipAddressComboBox->addItem(LoadString("IDS_MANUAL"));
    ui->ipAddressComboBox->setCurrentIndex(0);

    ui->ipLineEdit->SetMode(Mode::KeypadType);
    ui->subnetMaskLineEdit->SetMode(Mode::KeypadType);
    ui->gatewayLineEdit->SetMode(Mode::KeypadType);
    ui->dnsServerLineEdit->SetMode(Mode::KeypadType);


}

Setting5Widget::~Setting5Widget()
{
    delete ui;
}

void Setting5Widget::setDHCPMode()
{
    ui->IpLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->ipLineEdit->setDisabled(true);
    ui->gatewayLabel->hide();
    ui->subnetMaskLabel->hide();
    ui->dnsServerLabel->hide();
    ui->subnetMaskLineEdit->hide();
    ui->gatewayLineEdit->hide();
    ui->dnsServerLineEdit->hide();
    ui->gridLayout->addItem(new QSpacerItem(ui->subnetMaskLineEdit->size().width(), ui->subnetMaskLineEdit->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 1);
    ui->gridLayout->addItem(new QSpacerItem(ui->gatewayLineEdit->size().width(), ui->gatewayLineEdit->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 6, 1);
    ui->gridLayout->addItem(new QSpacerItem(ui->dnsServerLineEdit->size().width(), ui->dnsServerLineEdit->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 1);

    // 시연용
    ui->ipLineEdit->setText("20:0D:B0:1E:1C:57");
}

void Setting5Widget::setManualMode()
{
    if ( ui->gridLayout->rowCount() > 6)
    {
        delete ui->gridLayout->itemAtPosition(5, 1)->widget();
        delete ui->gridLayout->itemAtPosition(6, 1)->widget();
        delete ui->gridLayout->itemAtPosition(7, 1)->widget();
        ui->gridLayout->removeItem(ui->gridLayout->itemAtPosition(5, 1));
        ui->gridLayout->removeItem(ui->gridLayout->itemAtPosition(6, 1));
        ui->gridLayout->removeItem(ui->gridLayout->itemAtPosition(7, 1));
    }
    ui->ipLineEdit->setDisabled(false);
    ui->gatewayLabel->show();
    ui->subnetMaskLabel->show();
    ui->dnsServerLabel->show();
    ui->subnetMaskLineEdit->show();
    ui->gatewayLineEdit->show();
    ui->dnsServerLineEdit->show();
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->dnsServerLabel->setText(LoadString("IDS_DNS_SERVER"));

    // 시연용
    ui->ipLineEdit->setText("192.168.10.40");
    ui->subnetMaskLineEdit->setText("255.255.255.0");
    ui->gatewayLineEdit->setText("192.168.0.1");
    ui->dnsServerLineEdit->setText("168.xxx.xxx.1");

}

void Setting5Widget::on_ipAddressComboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
    {
        setDHCPMode();
    }
        break;
    case 1:
    {
        setManualMode();
    }
        break;
    }
}

