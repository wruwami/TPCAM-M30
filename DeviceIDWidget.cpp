#include "DeviceIDWidget.h"
#include "ui_DeviceIDWidget.h"

#include "StringLoader.h"
#include "KeyboardDialog.h"
#include "ConfigManager.h"

DeviceIDWidget::DeviceIDWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceIDWidget)
{
    ui->setupUi(this);

    m_pSaveButton = ui->savePushButton;
    m_pCancelButton = ui->cancelPushButton;

    ui->deviceIDLabel->setText(LoadString("IDS_DEVICE_ID"));
    ui->deviceIDLabel->setFontSize(23);
    ui->deviceIDLabel_2->setText(LoadString("IDS_DEVICE_ID"));
    ui->deviceIDLabel_2->setFontSize(23);
    ui->changeSSIDnFTPLabel->setText(LoadString("IDS_CHANGE_SSID_AND_FTP"));
    ui->changeSSIDnFTPLabel->setFontSize(23);


    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->savePushButton->setFontSize(23);
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cancelPushButton->setFontSize(23);
    ui->inputPushButton->setImage("Login", "keyboard.bmp");

    ui->checkBox->setChecked(true);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ConfigManager config = ConfigManager("setting_device_ID.json");
    QJsonObject object = config.GetConfig();
    QJsonObject object2 = object["Device ID"].toObject();

    QString SerialNum;
    if (QString::compare(object2["Prefix"].toString(), "null", Qt::CaseInsensitive) && !object2["Prefix"].toString().isEmpty())
        SerialNum.append(object2["Prefix"].toString() + "_" + object2["SerialNum"].toString());
    else
        SerialNum.append(object2["SerialNum"].toString());
    if (QString::compare(object2["Postfix"].toString(), "null", Qt::CaseInsensitive) && !object2["Postfix"].toString().isEmpty())
        SerialNum.append("_" + object2["Postfix"].toString());


    ui->lineEdit->setText(SerialNum);
}

DeviceIDWidget::~DeviceIDWidget()
{
    delete ui;
}

void DeviceIDWidget::on_inputPushButton_clicked()
{
    KeyboardDialog keyboardDialog(ui->lineEdit->text(), GetLanguage());
    if (keyboardDialog.exec() == QDialog::Accepted)
    {
        ui->lineEdit->setText(keyboardDialog.str());
    }
}

void DeviceIDWidget::on_savePushButton_clicked()
{
    QString deviceID = ui->lineEdit->text();

    if (ui->checkBox->isChecked())
    {
        ConfigManager config = ConfigManager("parameter_setting4.json");
        QString deviceID = ui->lineEdit->text();
        QJsonObject object = config.GetConfig();
        object["wiFi SSID"] = deviceID;
        object["sta ftp id & p/w"] = deviceID;
        config.SetConfig(object);
        config.SaveFile();

    }

    ConfigManager config = ConfigManager("setting_device_ID.json");
    QJsonObject object = config.GetConfig();
    QJsonObject object2;
//    object[]
    QStringList deviceIDList = deviceID.split("_");
    if (deviceIDList.size() == 3)
    {

        object2["Prefix"] = deviceIDList[0];
        object2["SerialNum"] = deviceIDList[1];
        object2["Postfix"] = deviceIDList[2];
    }
    else if (deviceIDList.size() == 2)
    {
        object2["Prefix"] = deviceIDList[0];
        object2["SerialNum"] = deviceIDList[1];
        object2["Postfix"] = "null";
    }
    else
    {
        object2["Prefix"] = "null";
        object2["SerialNum"] = deviceIDList[0];
        object2["Postfix"] = "null";
    }
    object["Device ID"] = object2;
    config.SetConfig(object);
    config.SaveFile();
}

