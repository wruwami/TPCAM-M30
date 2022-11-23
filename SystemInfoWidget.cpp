#include "SystemInfoWidget.h"
#include "ui_SystemInfoWidget.h"

#include "StringLoader.h"

SystemInfoWidget::SystemInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInfoWidget)
{
    ui->setupUi(this);

    ui->alignLabel->setText(LoadString("IDS_ALIGN"));
    ui->modeLabel->setText(LoadString("IDS_MODE"));
    ui->camLabel->setText(LoadString("IDS_CAM"));
    ui->laserLabel->setText(LoadString("IDS_LASER"));
    ui->serialNumberLabel->setText(LoadString("IDS_SERIAL_NUMBER"));
}

SystemInfoWidget::~SystemInfoWidget()
{
    delete ui;
}
