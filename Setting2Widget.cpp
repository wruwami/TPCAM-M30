#include "Setting2Widget.h"
#include "ui_Setting2Widget.h"

Setting2Widget::Setting2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting2Widget)
{
    ui->setupUi(this);

    ui->reticleShapeLabel->setText("IDS_RETICLE_SHAPE");
    ui->weatherModeLabel->setText("IDS_WEATHER_MODE");
    ui->daynNightLabel->setText("IDS_DAYNIGHT");
    ui->buzzerLabel->setText("IDS_BUZZER");
    ui->antiJammingModeLabel->setText("IDS_ANTI_JAMMING_MODE");
}

Setting2Widget::~Setting2Widget()
{
    delete ui;
}
