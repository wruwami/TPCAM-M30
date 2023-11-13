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
    ui->savePushButton->setFontSize(23);
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cancelPushButton->setFontSize(23);
    ui->timeZoneLabel->setText(LoadString("IDS_TIMEZONE"));
//    ui->timeZoneLabel->setFontSize(23);
    ui->gpsSyncCheckBox->setText(LoadString("IDS_GPS_SYNC"));
//    ui->gpsSyncCheckBox->setFontSize(23);
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
    ui->timeZoneComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_dateTime = m_dateTime.currentDateTime();

    m_pYearLabel = new CustomLabel;
    m_pYearLabel->setStyleSheet("background-color: rgb(255, 255, 255); \
            color: rgb(0, 0, 0); \
            border: 1px solid black;");
    m_pYearLabel->setAlignment(Qt::AlignCenter);
//    yearLabel->setText(LoadString("IDS_YEAR"));
    m_pMonthLabel = new CustomLabel;
    m_pMonthLabel->setStyleSheet("background-color: rgb(255, 255, 255); \
            color: rgb(0, 0, 0); \
            border: 1px solid black;");
    m_pMonthLabel->setAlignment(Qt::AlignCenter);
//
//    monthLabel->setText(LoadString("IDS_MONTH"));
    m_pDayLabel = new CustomLabel;
    m_pDayLabel->setStyleSheet("background-color: rgb(255, 255, 255); \
            color: rgb(0, 0, 0); \
            border: 1px solid black;");
    m_pDayLabel->setAlignment(Qt::AlignCenter);
//
//    dayLabel->setText(LoadString("IDS_DAY"));
    m_pYearPlusButton = new CustomPushButton;
    m_pYearPlusButton->setText("+");
    m_pYearMinusButton = new CustomPushButton;
    m_pYearMinusButton->setText("-");

    m_pMonthPlusButton = new CustomPushButton;
    m_pMonthPlusButton->setText("+");

    m_pMonthMinusButton = new CustomPushButton;
    m_pMonthMinusButton->setText("-");

    m_pDayPlusButton = new CustomPushButton;
    m_pDayPlusButton->setText("+");

    m_pDayMinusButton = new CustomPushButton;
    m_pDayMinusButton->setText("-");

    if (GetDateFormat() == YYYYMMDD)
    {
        ui->gridLayout->addWidget(m_pYearPlusButton,0,0);
        ui->gridLayout->addWidget(m_pYearLabel,1,0);
        ui->gridLayout->addWidget(m_pYearMinusButton,2,0);
        ui->gridLayout->addWidget(m_pMonthPlusButton,0,1);
        ui->gridLayout->addWidget(m_pMonthLabel,1,1);
        ui->gridLayout->addWidget(m_pMonthMinusButton,2,1);
        ui->gridLayout->addWidget(m_pDayPlusButton,0,2);
        ui->gridLayout->addWidget(m_pDayLabel,1,2);
        ui->gridLayout->addWidget(m_pDayMinusButton,2,2);

    }
    else if (GetDateFormat() == MMDDYYYY)
    {
        ui->gridLayout->addWidget(m_pMonthPlusButton,0,0);
        ui->gridLayout->addWidget(m_pMonthLabel,1,0);
        ui->gridLayout->addWidget(m_pMonthMinusButton,2,0);
        ui->gridLayout->addWidget(m_pDayPlusButton,0,1);
        ui->gridLayout->addWidget(m_pDayLabel,1,1);
        ui->gridLayout->addWidget(m_pDayMinusButton,2,1);
        ui->gridLayout->addWidget(m_pYearPlusButton,0,2);
        ui->gridLayout->addWidget(m_pYearLabel,1,2);
        ui->gridLayout->addWidget(m_pYearMinusButton,2,2);
    }
    else if (GetDateFormat() == DDMMYYYY)
    {
        ui->gridLayout->addWidget(m_pDayPlusButton,0,0);
        ui->gridLayout->addWidget(m_pDayLabel,1,0);
        ui->gridLayout->addWidget(m_pDayMinusButton,2,0);
        ui->gridLayout->addWidget(m_pMonthPlusButton,0,1);
        ui->gridLayout->addWidget(m_pMonthLabel,1,1);
        ui->gridLayout->addWidget(m_pMonthMinusButton,2,1);
        ui->gridLayout->addWidget(m_pYearPlusButton,0,2);
        ui->gridLayout->addWidget(m_pYearLabel,1,2);
        ui->gridLayout->addWidget(m_pYearMinusButton,2,2);
    }
    ui->gridLayout->setRowStretch(0, 1);
    ui->gridLayout->setRowStretch(1, 1);
    ui->gridLayout->setRowStretch(2, 1);
    ui->gridLayout->setColumnStretch(0, 1);
    ui->gridLayout->setColumnStretch(1, 1);
    ui->gridLayout->setColumnStretch(2, 1);

    connect(m_pYearPlusButton, SIGNAL(clicked()), this, SLOT(on_yearPlusPushButton_clicked()));
    connect(m_pYearMinusButton, SIGNAL(clicked()), this, SLOT(on_yearMinusPushButton_clicked()));
    connect(m_pMonthPlusButton, SIGNAL(clicked()), this, SLOT(on_monthPlusPushButton_clicked()));
    connect(m_pMonthMinusButton, SIGNAL(clicked()), this, SLOT(on_monthMinusPushButton_clicked()));
    connect(m_pDayPlusButton, SIGNAL(clicked()), this, SLOT(on_dayPlusPushButton_clicked()));
    connect(m_pDayMinusButton, SIGNAL(clicked()), this, SLOT(on_dayMinusPushButton_clicked()));

    setDateTimeValue();
}

DateTimeWidget::~DateTimeWidget()
{
    delete m_pYearLabel;// = new CustomLabel;
    delete  m_pMonthLabel;// = new CustomLabel;
    delete  m_pDayLabel;// = new CustomLabel;
    delete  m_pYearPlusButton;// = new CustomPushButton;
    delete  m_pYearMinusButton;// = new CustomPushButton;
    delete  m_pMonthPlusButton;// = new CustomPushButton;
    delete  m_pMonthMinusButton;// = new CustomPushButton;
    delete  m_pDayPlusButton;// = new CustomPushButton;
    delete  m_pDayMinusButton;// = new CustomPushButton;

    delete ui;
}

void DateTimeWidget::SetGPSUTCDateTime(QDateTime datetime)
{
    qint64 posixtime = datetime.currentSecsSinceEpoch();
    QString dateTimeString = ("sudo date +%s -s @");
    dateTimeString.append(QString::number(posixtime));

    int systemDateTimeStatus= system(dateTimeString.toStdString().c_str());
    if (systemDateTimeStatus == -1)
    {
        qDebug() << "Failed to change date time";
    }
}

void DateTimeWidget::setDateTimeValue()
{
    m_pYearLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().year())));
    m_pMonthLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().month())));
    m_pDayLabel->setText(QString::fromStdString(std::to_string(m_dateTime.date().day())));

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
    QString dateTimeString;

//    string.remove(0, 1)\;
//    string.remove(string.size() - 1, 1);
//    dateTimeString.append("TZ : " + ui->timeZoneComboBox->currentText());

    if (isChecked)
    {
        dateTimeString = ("sudo date +%s -s @");
        dateTimeString.append(QString::number(SerialGPSManager::GetInstance()->GetDateTime().toSecsSinceEpoch()));
    }
    else
    {
        dateTimeString = ("sudo date -s \"");
        dateTimeString.append(string);
    }
    dateTimeString.append("\"");
    int systemDateTimeStatus= system(dateTimeString.toStdString().c_str());


    if (systemDateTimeStatus == -1)
    {
        qDebug() << "Failed to change date time";
    }

    QString TimeZoneString ("sudo timedatectl set-timezone ");
    TimeZoneString.append(ui->timeZoneComboBox->currentText());
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
