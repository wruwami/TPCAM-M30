#include "Setting4STAWidget.h"
#include "ui_Setting4STAWidget.h"

#include <QJsonArray>

#include "StringLoader.h"
#include "BaseDialog.h"

Setting4STAWidget::Setting4STAWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4STAWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->wifiSSIDLabel->setText(LoadString("IDS_WIFI_SSID"));
    ui->FTPIDPWLabel->setText(LoadString("IDS_FTP_ID_PW"));
    ui->IpLabel->setText(LoadString("IDS_IP"));
    ui->subnetMaskLabel->setText(LoadString("IDS_SUBNET_MASK"));
    ui->printerLabel->setText(LoadString("IDS_PRINTER"));

//    ui->printerComboBox->addItem(LoadString("IDS_THERMAL_EAST"));
//    ui->printerComboBox->addItem(LoadString("IDS_THERMAL_WOOSIM"));
//    ui->printerComboBox->addItem(LoadString("IDS_BT_HP"));

    ui->wifiSSIDComboBox->addItem(m_jsonObject["sta ssid"].toString());

    foreach (QJsonValue json, m_jsonObject["printer items"].toArray())
    {
        ui->printerComboBox->addItem(json.toString());
    }
    int index = m_jsonObject["printer selection"].toInt() - 1;
    ui->printerComboBox->setCurrentIndex(index);

    ui->FTPIDPWLineEdit->setText(m_jsonObject["sta ftp id & pw"].toString());
    ui->ipLineEdit->setText(m_jsonObject["ip"].toString());
    ui->subnetMaskLineEdit->setText(m_jsonObject["subnet mask"].toString());
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
