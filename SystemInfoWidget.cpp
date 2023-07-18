#include "SystemInfoWidget.h"
#include "ui_SystemInfoWidget.h"

#include <QPainter>
#include <QPen>

#include "StringLoader.h"

SystemInfoWidget::SystemInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInfoWidget)
{
    ui->setupUi(this);

    ui->alignLabel->setText(LoadString("IDS_ALIGN"));
    ui->modeLabel->setText(LoadString("IDS_MODE"));
    ui->camLabel->setText(LoadString("IDS_CAM"));
    ui->laserLabel->setText(LoadString("IDS_LASER"));
    ui->serialNumberLabel->setText(LoadString("IDS_SERIAL_NUMBER"));
}

SystemInfoWidget::~SystemInfoWidget()
{
    delete ui;
}

void SystemInfoWidget::paintEvent(QPaintEvent *event)
{
    QPen Pen(Qt::black);
    Pen.setStyle(Qt::DashLine);
    QPainter painter(this);
    painter.setPen(Pen);

    painter.drawLine(0, height()/5, width(), height()/5);
    painter.drawLine(0, height()/5 * 2, width(), height()/5*2);
    painter.drawLine(0, height()/5 * 3, width(), height()/5*3);
    painter.drawLine(0, height()/5 * 4, width(), height()/5*4);
}
