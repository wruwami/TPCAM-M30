#include "Setting7Widget.h"
#include "ui_Setting7Widget.h"

#include "StringLoader.h"

Setting7Widget::Setting7Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting7Widget)
{
    ui->setupUi(this);

    ui->WifiLabel->setText(LoadString("IDS_WIFI"));
    ui->blueToothLabel->setText(LoadString("IDS_BLUETOOTH"));
    ui->nineAxisSensorLabel->setText(LoadString("IDS_NINE_AXIS_SENSOR"));
    ui->micnSpeackerLabel->setText(LoadString("IDS_MIC_N_SPEAKER"));
    ui->powerSavingTimeLabel->setText(LoadString("IDS_POWER_SAVING_TIME"));
}

Setting7Widget::~Setting7Widget()
{
    delete ui;
}
