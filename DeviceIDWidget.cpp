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

    QString Prefix = object2["Prefix"].toString();
    QString SerialNum = object2["SerialNum"].toString();
    QString Postfix = object2["Postfix"].toString();



//    ui->lineEdit->setText("TP0002000");
}

DeviceIDWidget::~DeviceIDWidget()
{
    delete ui;
}

void DeviceIDWidget::on_inputPushButton_clicked()
{
    KeyboardDialog keyboardDialog(GetLanguage());
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
//    object[]
    QStringList deviceIDList = deviceID.split("_");
    if (deviceIDList.size() == 2)
    {
        object["Device ID"].toObject()["Prefix"] = deviceIDList[0];
        object["Device ID"].toObject()["SerialNum"] = deviceIDList[1];
        object["Device ID"].toObject()["Postfix"] = deviceIDList[2];
    }
    else if (deviceIDList.size() == 1)
    {
        object["Device ID"].toObject()["Prefix"] = deviceIDList[0];
        object["Device ID"].toObject()["SerialNum"] = deviceIDList[1];
        object["Device ID"].toObject()["Postfix"] = "null";
    }
    else
    {
        object["Device ID"].toObject()["Prefix"] = "null";
        object["Device ID"].toObject()["SerialNum"] = deviceIDList[0];
        object["Device ID"].toObject()["Postfix"] = "null";
    }
    config.SetConfig(object);
    config.SaveFile();
}

