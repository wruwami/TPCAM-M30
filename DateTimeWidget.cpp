#include "DateTimeWidget.h"
#include "ui_DateTimeWidget.h"

#include <QTimeZone>
#include <QDebug>

#include "ConfigManager.h"
#include "DateFormatManager.h"
#include "StringLoader.h"
#include "CustomCheckBox.h"
#include "SerialGPSManager.h"

DateTimeWidget::DateTimeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTimeWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->timeZoneLabel->setText(LoadString("IDS_TIMEZONE"));
    ui->gpsSyncCheckBox->setText(LoadString("IDS_GPS_SYNC"));
    ui->gpsSyncCheckBox->setChecked(m_jsonObject["gps sync"].toBool());

    m_pSavePushButton = ui->savePushButton;
    m_pCancelPushButton = ui->cancelPushButton;
    m_pGPSCheckBox = ui->gpsSyncCheckBox;

    m_pParent = parent;

    QList<QByteArray> ids = QTimeZone::availableTimeZoneIds();
    foreach (QByteArray id, ids) {
        ui->timeZoneComboBox->addItem(id);
    }
    ui->timeZoneComboBox->setCurrentIndex(m_jsonObject["timezone select"].toInt() - 1);
    m_dateTime = m_dateTime.currentDateTime();
    setDateTimeValue();
}

DateTimeWidget::~DateTimeWidget()
{
    delete ui;
}

void DateTimeWidget::SetGPSUTCDateTime(QDateTime datetime)
{
    QByteArray tz = ui->timeZoneComboBox->currentText().toUtf8();
    m_dateTime = QDateTime(datetime.date(), datetime.time(), QTimeZone(tz));
}

void DateTimeWidget::setDateTimeValue()
{
    ui->yearLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().year())));
    ui->monthLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().month())));
    ui->dayLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().day())));
    ui->hourLabel->setText(QString::fromStdString(std::to_string(m_dateTime.time().hour())));
    ui->minuteLabel->setText(QString::fromStdString(std::to_string(m_dateTime.time().minute())));
    ui->secondLabel->setText(QString::fromStdString(std::to_string(m_dateTime.time().second())));

//    QString string = m_dateTime.toString("\"yyyy-MM-dd hh:mm:ss\"");
//    QString dateTimeString ("date -s ");
//    dateTimeString.append(string);
//    int systemDateTimeStatus= system(dateTimeString.toStdString().c_str());
//    if (systemDateTimeStatus == -1)
//    {
//        qDebug() << "Failed to change date time";
//    }
//    int systemHwClockStatus = system("/sbin/hwclock -w");
//    if (systemHwClockStatus == -1 )
//    {
//        qDebug() << "Failed to sync hardware clock";
//    }
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

void DateTimeWidget::on_savePushButton_clicked()
{
    m_newJsonObject["gps sync"] = ui->gpsSyncCheckBox->isChecked();
    bool isChecked = ui->gpsSyncCheckBox->isChecked();

    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

#ifdef  Q_OS_LINUX
    QString string = m_dateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString dateTimeString ("date -s \"");

//    string.remove(0, 1)\;
//    string.remove(string.size() - 1, 1);
//    dateTimeString.append("TZ : " + ui->timeZoneComboBox->currentText());

    if (isChecked)
    {
        dateTimeString.append(SerialGPSManager::GetInstance()->GetDateTimeString());
    }
    else
    {
        dateTimeString.append(string);
    }
    dateTimeString.append("\"");
    int systemDateTimeStatus= system(dateTimeString.toStdString().c_str());


    if (systemDateTimeStatus == -1)
    {
        qDebug() << "Failed to change date time";
    }

    QString TimeZoneString ("timedatectl set-timezone ");
    TimeZoneString.append(ui->timeZoneComboBox->currentText());
//    TimeZoneString.append("\"");
//    TimeZoneString.remove('\"');
    systemDateTimeStatus= system(TimeZoneString.toStdString().c_str());
    if (systemDateTimeStatus == -1)
    {
        qDebug() << "Failed to change time zone";
    }




#endif
}

void DateTimeWidget::on_cancelPushButton_clicked()
{
}

void DateTimeWidget::on_timeZoneComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["timezone select"] = index + 1;
}
