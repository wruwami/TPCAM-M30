#include "Setting5Widget.h"
#include "ui_Setting5Widget.h"

#include "StringLoader.h"

Setting5Widget::Setting5Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting5Widget)
{
    ui->setupUi(this);

    ui->ipAddressLabel->setText(LoadString("IDS_IP"));
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));
}

Setting5Widget::~Setting5Widget()
{
    delete ui;
}
