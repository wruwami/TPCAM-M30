#include "Setting4STAWidget.h"
#include "ui_Setting4STAWidget.h"

#include <QJsonArray>

#include "StringLoader.h"
#include "BaseDialog.h"
#include "KeyboardDialog.h"

Setting4STAWidget::Setting4STAWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4STAWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->searchPushButton->setText(LoadString("IDS_SEARCH"));
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

    ui->FTPIDPWLineEdit->setText(m_jsonObject["sta ftp id & p/w"].toString());
    ui->ipLineEdit->setText(m_jsonObject["ip"].toString());
    ui->subnetMaskLineEdit->setText(m_jsonObject["subnet mask"].toString());
}

Setting4STAWidget::~Setting4STAWidget()
{
    if (m_isSave)
    {
        m_config.SetConfig(m_newJsonObject);
        m_config.SaveFile();
    }

    delete ui;
}

void Setting4STAWidget::on_pwPushButton_clicked()
{
    KeyboardDialog keyboardDialog(GetLanguage());
    if (keyboardDialog.exec() == QDialog::Accepted)
    {
        m_newJsonObject["sta ftp p/w"] = keyboardDialog.str();
    }
}

void Setting4STAWidget::on_FTPIDPWLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["sta ftp id & p/w"] = arg1;
}

void Setting4STAWidget::on_ipLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["ip"] = arg1;
}

void Setting4STAWidget::on_subnetMaskLineEdit_textChanged(const QString &arg1)
{
    m_newJsonObject["subnet mask"] = arg1;
}

void Setting4STAWidget::on_printerComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["printer selection"] = index + 1;
}


void Setting4STAWidget::on_searchPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::WifiSearchWidgetType, Qt::AlignmentFlag::AlignLeft, "");
    baseDialog.exec();
}

