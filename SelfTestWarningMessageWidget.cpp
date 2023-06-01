#include "SelfTestWarningMessageWidget.h"
#include "ui_SelfTestWarningMessageWidget.h"

#include "StringLoader.h"

SelfTestWarningMessageWidget::SelfTestWarningMessageWidget(bool isCamera, bool isLaser, bool isBattery, bool isStorage, QDialog *parent) :
    QWidget(parent),
    ui(new Ui::SelfTestWarningMessageWidget)
{
    m_pParent = parent;
    ui->setupUi(this);

    ui->label->setText(LoadString("IDS_NOT_WORKING_NORMALLY"));
    ui->label_2->setText(LoadString("IDS_CONTINUE_QUESTION"));

    ui->cameraLabel->setText(LoadString("IDS_CAMERA"));
    ui->storageLabel->setText(LoadString("IDS_STORAGE"));
    ui->laserLabel->setText(LoadString("IDS_LASER"));
    ui->batteryLabel->setText(LoadString("IDS_BATTERY"));

    if (isCamera)
        ui->cameraValueLabel->setText(LoadString("IDS_PASS"));
    else
        ui->cameraValueLabel->setText(LoadString("IDS_FAIL"));

    if (isLaser)
        ui->laserValueLabel->setText(LoadString("IDS_PASS"));
    else
        ui->laserValueLabel->setText(LoadString("IDS_FAIL"));

    if (isBattery)
        ui->batteryValueLabel->setText(LoadString("IDS_PASS"));
    else
        ui->batteryValueLabel->setText(LoadString("IDS_FAIL"));

    if (isStorage)
        ui->storageValueLabel->setText(LoadString("IDS_PASS"));
    else
        ui->storageValueLabel->setText(LoadString("IDS_FAIL"));


    ui->continuePushButton->setText(LoadString("IDS_CONTINUE"));
    ui->powerOffPushButton->setText(LoadString("IDS_POWER_OFF"));
}

SelfTestWarningMessageWidget::~SelfTestWarningMessageWidget()
{
    delete ui;
}

void SelfTestWarningMessageWidget::on_continuePushButton_clicked()
{
    m_pParent->accept();
}

void SelfTestWarningMessageWidget::on_powerOffPushButton_clicked()
{
    m_pParent->reject();
}
