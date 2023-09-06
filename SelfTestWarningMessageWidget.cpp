#include "SelfTestWarningMessageWidget.h"
#include "ui_SelfTestWarningMessageWidget.h"

#include "StringLoader.h"
#include "SelfTestWidget.h"

SelfTestWarningMessageWidget::SelfTestWarningMessageWidget(Status isCamera, Status isLaser, Status isBattery, Status isStorage, QDialog *parent) :
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

    if (isCamera == Pass)
    {
        ui->cameraValueLabel->setText(LoadString("IDS_PASS"));
    }
    else if (isCamera == Fail)
    {
        ui->cameraValueLabel->setText(LoadString("IDS_FAIL"));
        ui->cameraValueLabel->setColor(Qt::red);
        ui->cameraLabel->setColor(Qt::red);
    }

    if (isLaser == Pass)
    {
        ui->laserValueLabel->setText(LoadString("IDS_PASS"));
    }
    else if (isLaser == Fail)
    {
        ui->laserValueLabel->setText(LoadString("IDS_FAIL"));
        ui->laserValueLabel->setColor(Qt::red);
        ui->laserLabel->setColor(Qt::red);
    }
    if (isBattery == Pass)
    {
        ui->batteryValueLabel->setText(LoadString("IDS_PASS"));
    }
    else if (isBattery == Fail)
    {
        ui->batteryValueLabel->setText(LoadString("IDS_FAIL"));
        ui->batteryValueLabel->setColor(Qt::red);
        ui->batteryLabel->setColor(Qt::red);
    }

    if (isStorage == Pass)
    {
        ui->storageValueLabel->setText(LoadString("IDS_PASS"));
    }
    else if (isStorage == Fail)
    {
        ui->storageValueLabel->setText(LoadString("IDS_FAIL"));
        ui->storageValueLabel->setColor(Qt::red);
        ui->storageLabel->setColor(Qt::red);
    }


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
