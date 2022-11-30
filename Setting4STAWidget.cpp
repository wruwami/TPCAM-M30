#include "Setting4STAWidget.h"
#include "ui_Setting4STAWidget.h"

#include "StringLoader.h"
#include "BaseDialog.h"

Setting4STAWidget::Setting4STAWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4STAWidget)
{
    ui->setupUi(this);

    ui->wifiSSIDLabel->setText(LoadString("IDS_WIFI_SSID"));
    ui->FTPIDPWLabel->setText(LoadString("IDS_FTP_ID_PW"));
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->printerLabel->setText(LoadString("IDS_PRINTER"));
}

Setting4STAWidget::~Setting4STAWidget()
{
    delete ui;
}

void Setting4STAWidget::on_searchPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::WifiSearchWidgetType);
    baseDialog.exec();
}

void Setting4STAWidget::on_pwPushButton_clicked()
{

}
