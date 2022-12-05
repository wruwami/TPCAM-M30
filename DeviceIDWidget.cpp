#include "DeviceIDWidget.h"
#include "ui_DeviceIDWidget.h"

#include "StringLoader.h"

DeviceIDWidget::DeviceIDWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceIDWidget)
{
    ui->setupUi(this);

    ui->deviceIDLabel->setText(LoadString("IDS_DEVICE_ID"));
    ui->deviceIDLabel_2->setText(LoadString("IDS_DEVICE_ID"));
    ui->changeSSIDnFTPLabel->setText(LoadString("IDS_CHANGE_SSID_AND_FTP"));


    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->inputPushButton->setImage("Login", "keyboard.bmp");

}

DeviceIDWidget::~DeviceIDWidget()
{
    delete ui;
}

void DeviceIDWidget::on_inputPushButton_clicked()
{

}
