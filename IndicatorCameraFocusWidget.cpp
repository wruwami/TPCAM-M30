#include "IndicatorCameraFocusWidget.h"
#include "ui_IndicatorCameraFocusWidget.h"

IndicatorCameraFocusWidget::IndicatorCameraFocusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorCameraFocusWidget)
{
    ui->setupUi(this);
}

IndicatorCameraFocusWidget::~IndicatorCameraFocusWidget()
{
    delete ui;
}
