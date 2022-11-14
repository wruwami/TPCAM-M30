#include "IndicatorCameraWidget.h"
#include "ui_IndicatorCameraWidget.h"

IndicatorCameraWidget::IndicatorCameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorCameraWidget)
{
    ui->setupUi(this);
}

IndicatorCameraWidget::~IndicatorCameraWidget()
{
    delete ui;
}
