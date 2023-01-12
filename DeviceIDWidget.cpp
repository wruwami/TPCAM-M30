#include "DeviceIDWidget.h"
#include "ui_DeviceIDWidget.h"

#include "StringLoader.h"
#include "KeyboardDialog.h"

DeviceIDWidget::DeviceIDWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceIDWidget)
{
    ui->setupUi(this);

    m_pSaveButton = ui->savePushButton;
    m_pCancelButton = ui->cancelPushButton;

    ui->deviceIDLabel->setText(LoadString("IDS_DEVICE_ID"));
    ui->deviceIDLabel_2->setText(LoadString("IDS_DEVICE_ID"));
    ui->changeSSIDnFTPLabel->setText(LoadString("IDS_CHANGE_SSID_AND_FTP"));


    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->inputPushButton->setImage("Login", "keyboard.bmp");

    ui->checkBox->setChecked(true);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 시연용
    ui->lineEdit->setText("TP0002000");
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
