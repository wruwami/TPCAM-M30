#include "IndicatorGPSWidget.h"
#include "ui_IndicatorGPSWidget.h"

#include "StringLoader.h"

IndicatorGPSWidget::IndicatorGPSWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorGPSWidget)
{
    ui->setupUi(this);

    ui->sensitivityeLabel->setText(LoadString("IDS_SENSITIVITY");
    ui->timeLabel->setText(LoadString("IDS_TIME");
    ui->latitudeLabel->setText(LoadString("IDS_LATITUDE");
    ui->longitudeLabel->setText(LoadString("IDS_LONGITUDE");
    ui->numberOfSatellitesLabel->setText(LoadString("IDS_NUMBER_OF_SATELLITES");
}

IndicatorGPSWidget::~IndicatorGPSWidget()
{
    delete ui;
}
