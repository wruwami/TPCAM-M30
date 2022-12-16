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

    ui->wifiComboBox->addItem(LoadString("IDS_ON"));
    ui->wifiComboBox->addItem(LoadString("IDS_OFF"));

    ui->bluetoothComboBox->addItem(LoadString("IDS_ON"));
    ui->bluetoothComboBox->addItem(LoadString("IDS_OFF"));

    ui->nineAxisSensorComboBox->addItem(LoadString("IDS_ON"));
    ui->nineAxisSensorComboBox->addItem(LoadString("IDS_OFF"));

    ui->micnSpeackerComboBox->addItem(LoadString("IDS_ON"));
    ui->micnSpeackerComboBox->addItem(LoadString("IDS_OFF"));

    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_OFF"));
    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_10_MINUTE"));
    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_20_MINUTE"));
    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_30_MINUTE"));
    ui->powerSavingTimeComboBox->setCurrentIndex(2);

}

Setting7Widget::~Setting7Widget()
{
    delete ui;
}
