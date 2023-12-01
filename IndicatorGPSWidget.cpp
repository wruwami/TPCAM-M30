#include "IndicatorGPSWidget.h"
#include "ui_IndicatorGPSWidget.h"

#include <QPen>
#include <QPainter>
#include <QTimeZone>
#include <QDate>
#include <QTime>

#include "StringLoader.h"
#include "SerialGPSManager.h"
#include "ConfigManager.h"
#include "DateFormatManager.h"

IndicatorGPSWidget::IndicatorGPSWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorGPSWidget)
{
    ui->setupUi(this);

//    SerialGPSManager* m_serialGPSManager = new SerialGPSManager;

    ui->sensitivityeLabel->setText(LoadString("IDS_SENSITIVITY"));
//    ui->sensitivityeLabel->setFontSize(23);
    ui->timeLabel->setText(LoadString("IDS_TIME") + SerialGPSManager::GetInstance()->GetDateTimeString());
//    ui->timeLabel->setFontSize(23);
    ui->latitudeLabel->setText(LoadString("IDS_LATITUDE") + SerialGPSManager::GetInstance()->GetLatitude());
//    ui->latitudeLabel->setFontSize(23);
    ui->longitudeLabel->setText(LoadString("IDS_LONGITUDE") + SerialGPSManager::GetInstance()->GetLongitude());
//    ui->longitudeLabel->setFontSize(23);
    ui->numberOfSatellitesLabel->setText(LoadString("IDS_NUMBER_OF_SATELLITES") + QString::number(SerialGPSManager::GetInstance()->GetSatellitesInView()));
//    ui->numberOfSatellitesLabel->setFontSize(23);

    QJsonObject object = ConfigManager("setting_daytime.json").GetConfig();
    QList<QByteArray> ids = QTimeZone::availableTimeZoneIds();
    m_tz = ids[object["timezone select"].toInt() - 1];

    startTimer(1000);
}

IndicatorGPSWidget::~IndicatorGPSWidget()
{
//    if (m_serialGPSManager != nullptr)
//    {
//        delete m_serialGPSManager;
//        m_serialGPSManager = nullptr;
//    }
    delete ui;
}

void IndicatorGPSWidget::paintEvent(QPaintEvent *event)
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

void IndicatorGPSWidget::timerEvent(QTimerEvent *event)
{
    ui->sensitivityeLabel->setText(LoadString("IDS_SENSITIVITY") + SerialGPSManager::GetInstance()->GetSensitivity());
    QDateTime datetime;
    QString strDateTime;

    if (SerialGPSManager::GetInstance()->GetSatellitesInView() >= 3)
    {
        datetime = SerialGPSManager::GetInstance()->GetDateTime();
        strDateTime = GetDate(QDateTime(datetime.date(), datetime.time(), QTimeZone(m_tz)).toString("yyyyMMdd"));
        strDateTime.append(" " + QDateTime(datetime.date(), datetime.time(), QTimeZone(m_tz)).toString("hh:mm:ss"));
    }
    else
    {
        strDateTime = GetDate(QDateTime::currentDateTime().toString("yyyyMMdd"));
        strDateTime.append(" " + QDateTime::currentDateTime().toString("hh:mm:ss"));
    }
    ui->timeLabel->setText(LoadString("IDS_TIME") + strDateTime);
    ui->latitudeLabel->setText(LoadString("IDS_LATITUDE") + SerialGPSManager::GetInstance()->GetLatitude());
    ui->longitudeLabel->setText(LoadString("IDS_LONGITUDE") + SerialGPSManager::GetInstance()->GetLongitude());
    ui->numberOfSatellitesLabel->setText(LoadString("IDS_NUMBER_OF_SATELLITES") + QString::number(SerialGPSManager::GetInstance()->GetSatellitesInView()));
}
