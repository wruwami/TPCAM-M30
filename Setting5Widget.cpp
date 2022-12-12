#include "Setting5Widget.h"
#include "ui_Setting5Widget.h"

#include <QSpacerItem>

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

//    QSizePolicy sp_retain = sizePolicy();
//    sp_retain.setRetainSizeWhenHidden(true);

//    ui->lineEdit_2->setSizePolicy(sp_retain);
//    ui->lineEdit_3->setSizePolicy(sp_retain);
//    ui->lineEdit_4->setSizePolicy(sp_retain);

}

Setting5Widget::~Setting5Widget()
{
    delete ui;
}

void Setting5Widget::setDHCPMode()
{
    ui->IpLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->lineEdit->setDisabled(true);
    ui->gatewayLabel->hide();
    ui->subnetMaskLabel->hide();
    ui->dnsServerLabel->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->gridLayout->addItem(new QSpacerItem(ui->lineEdit_2->size().width(), ui->lineEdit_2->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 1);
    ui->gridLayout->addItem(new QSpacerItem(ui->lineEdit_3->size().width(), ui->lineEdit_3->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 6, 1);
    ui->gridLayout->addItem(new QSpacerItem(ui->lineEdit_4->size().width(), ui->lineEdit_4->size().height(), QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 1);
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
    ui->gatewayLabel->show();
    ui->subnetMaskLabel->show();
    ui->dnsServerLabel->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->gatewayLabel->setText(LoadString("IDS_GATEWAY"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->dnsServerLabel->setText(LoadString("IDS_DNS_SERVER"));

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

