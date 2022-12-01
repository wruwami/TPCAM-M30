#include "Setting2Widget.h"
#include "ui_Setting2Widget.h"

#include "StringLoader.h"

Setting2Widget::Setting2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting2Widget)
{
    ui->setupUi(this);

    ui->reticleShapeLabel->setText(LoadString("IDS_RETICLE_SHAPE"));
    ui->weatherModeLabel->setText(LoadString("IDS_WEATHER_MODE"));
    ui->daynNightLabel->setText(LoadString("IDS_DAYNIGHT"));
    ui->buzzerLabel->setText(LoadString("IDS_BUZZER"));
    ui->antiJammingModeLabel->setText(LoadString("IDS_ANTI_JAMMING_MODE"));

    ui->reticleShapeComboBox->addItem(LoadString("IDS_CROSS"));
    ui->reticleShapeComboBox->addItem(LoadString("IDS_DOT"));
    ui->reticleShapeComboBox->addItem(LoadString("IDS_ROUND"));
    ui->reticleShapeComboBox->addItem(LoadString("IDS_RECTANGLE"));

    ui->weatherModeComboBox->addItem(LoadString("IDS_SUNNY"));

    ui->daynNightComboBox->addItem(LoadString("IDS_DAY_DARK"));
    ui->daynNightComboBox->addItem(LoadString("IDS_DAY_STANDARD"));
    ui->daynNightComboBox->addItem(LoadString("IDS_DAY_BRIGHT"));
    ui->daynNightComboBox->addItem(LoadString("IDS_NIGHT_DARK"));
    ui->daynNightComboBox->addItem(LoadString("IDS_NIGHT_STANDARD"));
    ui->daynNightComboBox->addItem(LoadString("IDS_NIGHT_BRIGHT"));

    ui->buzzerComboBox->addItem(LoadString("IDS_ON"));
    ui->buzzerComboBox->addItem(LoadString("IDS_OFF"));

    ui->antiJammingModeComboBox->addItem(LoadString("IDS_ON"));
    ui->antiJammingModeComboBox->addItem(LoadString("IDS_OFF"));

}

Setting2Widget::~Setting2Widget()
{
    delete ui;
}
