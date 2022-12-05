#include "IndicatorCameraExposeWidget.h"
#include "ui_IndicatorCameraExposeWidget.h"

#include "StringLoader.h"

IndicatorCameraExposeWidget::IndicatorCameraExposeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorCameraExposeWidget)
{
    ui->setupUi(this);

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
//    ui->

}

IndicatorCameraExposeWidget::~IndicatorCameraExposeWidget()
{
    delete ui;
}
