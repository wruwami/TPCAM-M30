#include "DateTimeWidget.h"
#include "ui_DateTimeWidget.h"

DateTimeWidget::DateTimeWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateTimeWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    m_cancelButton = ui->cancelPushButton;
//    m_dateTime
}

DateTimeWidget::~DateTimeWidget()
{
    delete ui;
}

void DateTimeWidget::on_yearPlusPushButton_clicked()
{

}

void DateTimeWidget::on_yearMinusPushButton_clicked()
{

}

void DateTimeWidget::on_monthPlusPushButton_clicked()
{

}

void DateTimeWidget::on_monthMinusPushButton_clicked()
{

}

void DateTimeWidget::on_dayPlusPushButton_clicked()
{

}

void DateTimeWidget::on_dayMinusPushButton_clicked()
{

}

void DateTimeWidget::on_hourPlusPushButton_clicked()
{

}

void DateTimeWidget::on_hourMinusPushButton_clicked()
{

}

void DateTimeWidget::on_minutePlusPushButton_clicked()
{

}

void DateTimeWidget::on_minuteMinusPushButton_clicked()
{

}

void DateTimeWidget::on_secondPlusPushButton_clicked()
{

}

void DateTimeWidget::on_secondMinusPushButton_clicked()
{

}
