#include "Setting5Widget.h"
#include "ui_Setting5Widget.h"

#include "StringLoader.h"

Setting5Widget::Setting5Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting5Widget)
{
    ui->setupUi(this);

    ui->ipAddressLabel->setText(LoadString("IDS_IP"));

    ui->ipAddressComboBox->addItem(LoadString("IDS_DHCP"));
    ui->ipAddressComboBox->addItem(LoadString("IDS_MANUAL"));
    ui->ipAddressComboBox->setCurrentIndex(0);
}

Setting5Widget::~Setting5Widget()
{
    delete ui;
}

void Setting5Widget::setDHCPMode()
{
    ui->IpLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->gatewayLabel->hide();
    ui->subnetMaskLabel->hide();
    ui->gatewayLabel->hide();

}

void Setting5Widget::setManualMode()
{
    ui->gatewayLabel->show();
    ui->subnetMaskLabel->show();
    ui->gatewayLabel->show();
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));

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

