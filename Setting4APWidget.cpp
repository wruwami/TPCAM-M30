#include "Setting4APWidget.h"
#include "ui_Setting4APWidget.h"

#include "StringLoader.h"

#include "BaseDialog.h"

Setting4APWidget::Setting4APWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4APWidget)
{
    ui->setupUi(this);

    ui->macAddressLabel->setText(LoadString("IDS_MAC_ADDRESS"));
    ui->wifiSSIDnFTPIDlabel->setText(LoadString("IDS_WIFISSID_AND_FTP_ID"));
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->printerLabel->setText(LoadString("IDS_PRINTER"));

    ui->printerComboBox->addItem(LoadString("IDS_THERMAL_EAST"));
    ui->printerComboBox->addItem(LoadString("IDS_THERMAL_WOOSIM"));
    ui->printerComboBox->addItem(LoadString("IDS_BT_HP"));

    ui->pwPushButton->setText(LoadString("IDS_PW"));

    ui->macAddressLineEdit->setDisabled(true);
    ui->ipLineEdit->SetMode(Mode::KeypadType);
    ui->macAddressLineEdit->SetMode(Mode::KeyboardType);

}

Setting4APWidget::~Setting4APWidget()
{
    delete ui;
}

void Setting4APWidget::on_pwPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::NetworkPWWidgetType, Qt::AlignmentFlag::AlignCenter);
    baseDialog.exec();
}
