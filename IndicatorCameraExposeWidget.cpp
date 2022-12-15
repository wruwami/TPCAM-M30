#include "IndicatorCameraExposeWidget.h"
#include "ui_IndicatorCameraExposeWidget.h"

#include "StringLoader.h"
#include "WidgetSize.h"

IndicatorCameraExposeWidget::IndicatorCameraExposeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorCameraExposeWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);

//    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 960)));
    setGeometry(GetWidgetSizePos(QRect(0, 272 + 125, 1600, 563)));

    ui->showHidePushButton->setText(LoadString("IDS_HIDE"));
    ui->speedPushButton->setText(LoadString("IDS_SPEED"));
//    ui->

}

IndicatorCameraExposeWidget::~IndicatorCameraExposeWidget()
{
    delete ui;
}

void IndicatorCameraExposeWidget::mousePressEvent(QMouseEvent *event)
{
    accept();
}
