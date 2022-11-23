#include "IndicatorGPSWidget.h"
#include "ui_IndicatorGPSWidget.h"

IndicatorGPSWidget::IndicatorGPSWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorGPSWidget)
{
    ui->setupUi(this);
}

IndicatorGPSWidget::~IndicatorGPSWidget()
{
    delete ui;
}
