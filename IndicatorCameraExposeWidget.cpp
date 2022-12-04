#include "IndicatorCameraExposeWidget.h"
#include "ui_IndicatorCameraExposeWidget.h"

IndicatorCameraExposeWidget::IndicatorCameraExposeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorCameraExposeWidget)
{
    ui->setupUi(this);
}

IndicatorCameraExposeWidget::~IndicatorCameraExposeWidget()
{
    delete ui;
}
