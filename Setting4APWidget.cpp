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

    // 시연용
    ui->macAddressLineEdit->setText("20:0D:B0:1E:1C:57");
    ui->wifiSSIDnFTPlineEdit->setText("TP30000");
    ui->ipLineEdit->setText("192.168.10.1");
    ui->subnetMaskLineEdit->setText("255.255.255.0");
}

Setting4APWidget::~Setting4APWidget()
{
    delete ui;
}

void Setting4APWidget::on_pwPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::AdminPWWidgetType, Qt::AlignmentFlag::AlignCenter, LoadString("IDS_PLEASE_INPUT_NETWORK_PASSWORD"));
    baseDialog.exec();
}
