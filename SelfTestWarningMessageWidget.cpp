#include "SelfTestWarningMessageWidget.h"
#include "ui_SelfTestWarningMessageWidget.h"

#include "StringLoader.h"

SelfTestWarningMessageWidget::SelfTestWarningMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfTestWarningMessageWidget)
{
    ui->setupUi(this);

    ui->label->setText(LoadString("IDS_WARNING_MESSAGE"));
    ui->label_2->setText(LoadString("IDS_CONTINUE_QUESTION"));

    ui->laserLabel->setText(LoadString("IDS_LASER"));
    ui->storageLabel->setText(LoadString("IDS_STORAGE"));
    ui->laserLabel->setText(LoadString("IDS_LASER"));
    ui->batteryLabel->setText(LoadString("IDS_BATTERY"));
    ui->laserValueLabel->setText(LoadString("IDS_FAIL"));
    ui->storageValueLabel->setText(LoadString("IDS_FAIL"));
    ui->laserValueLabel->setText(LoadString("IDS_FAIL"));
    ui->batteryValueLabel->setText(LoadString("IDS_FAIL"));

    ui->continuePushButton->setText(LoadString("IDS_CONTINUE"));
    ui->powerOffPushButton->setText(LoadString("IDS_POWER_OFF"));
}

SelfTestWarningMessageWidget::~SelfTestWarningMessageWidget()
{
    delete ui;
}
