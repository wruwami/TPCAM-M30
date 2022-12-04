#include "DateTimeWidget.h"
#include "ui_DateTimeWidget.h"

#include "StringLoader.h"

DateTimeWidget::DateTimeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTimeWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->timeZoneLabel->setText(LoadString("IDS_TIMEZONE"));
    ui->gpsSyncCheckBox->setText(LoadString("IDS_GPS_SYNC"));

    m_pSavePushButton = ui->savePushButton;
    m_pCancelPushButton = ui->cancelPushButton;

    m_dateTime = m_dateTime.currentDateTime();
    setDateTimeValue();
}

DateTimeWidget::~DateTimeWidget()
{
    delete ui;
}

void DateTimeWidget::setDateTimeValue()
{
    ui->yearLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().year())));
    ui->monthLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().month())));
    ui->dayLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().day())));
    ui->hourLabel->setText(QString::fromStdString(std::to_string(m_dateTime.time().hour())));
    ui->minuteLabel->setText(QString::fromStdString(std::to_string(m_dateTime.time().minute())));
    ui->secondLabel->setText(QString::fromStdString(std::to_string(m_dateTime.time().second())));
}

void DateTimeWidget::on_yearPlusPushButton_clicked()
{
    m_dateTime = m_dateTime.addYears(1);
    setDateTimeValue();
}

void DateTimeWidget::on_yearMinusPushButton_clicked()
{
    m_dateTime = m_dateTime.addYears(-1);
    setDateTimeValue();
}

void DateTimeWidget::on_monthPlusPushButton_clicked()
{
    m_dateTime = m_dateTime.addMonths(1);
    setDateTimeValue();
}

void DateTimeWidget::on_monthMinusPushButton_clicked()
{
    m_dateTime = m_dateTime.addMonths(-1);
    setDateTimeValue();
}

void DateTimeWidget::on_dayPlusPushButton_clicked()
{
    m_dateTime = m_dateTime.addDays(1);
    setDateTimeValue();
}

void DateTimeWidget::on_dayMinusPushButton_clicked()
{
    m_dateTime = m_dateTime.addDays(-1);
    setDateTimeValue();
}

void DateTimeWidget::on_hourPlusPushButton_clicked()
{
    m_dateTime = m_dateTime.addSecs(1 * 60 * 60);
    setDateTimeValue();
}

void DateTimeWidget::on_hourMinusPushButton_clicked()
{
    m_dateTime = m_dateTime.addSecs(-1 * 60 * 60);
    setDateTimeValue();
}

void DateTimeWidget::on_minutePlusPushButton_clicked()
{
    m_dateTime = m_dateTime.addSecs(1 * 60);
    setDateTimeValue();
}

void DateTimeWidget::on_minuteMinusPushButton_clicked()
{
    m_dateTime = m_dateTime.addSecs(-1 * 60);
    setDateTimeValue();
}

void DateTimeWidget::on_secondPlusPushButton_clicked()
{
    m_dateTime = m_dateTime.addSecs(1);
    setDateTimeValue();
}

void DateTimeWidget::on_secondMinusPushButton_clicked()
{
    m_dateTime = m_dateTime.addSecs(-1);
    setDateTimeValue();
}

//void DateTimeWidget::on_savePushButton_clicked()
//{
////    accept();
//}

//void DateTimeWidget::on_cancelPushButton_clicked()
//{
////    reject();
//}
