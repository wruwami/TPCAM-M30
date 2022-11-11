#include "Setting4Widget.h"
#include "ui_Setting4Widget.h"

#include "StringLoader.h"

Setting4Widget::Setting4Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4Widget)
{
    ui->setupUi(this);

    ui->macAddressLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->wifiSSIDnFTPIDlabel->setText(LoadString("IDS_WIFISSID_AND_FTP_ID"));
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->printerLabel->setText(LoadString("IDS_PRINTER"));

}

Setting4Widget::~Setting4Widget()
{
    delete ui;
}
