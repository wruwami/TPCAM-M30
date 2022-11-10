#include "SelfTestWidget.h"
#include "ui_SelfTestWidget.h"
#include <QDate>
#include <QTime>
#include <QFile>

#include "Color.h"
#include "StringLoader.h"

SelfTestWidget::SelfTestWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfTestWidget)
{
    ui->setupUi(this);

    setBackGroundColor(this, 0x000000);

    QFile file(":/style/selftestWidget.qss");
    file.open(QFile::ReadOnly);
    this->setStyleSheet(QString::fromLatin1(file.readAll()));


    this->setWindowFlags(Qt::FramelessWindowHint |Qt::Window);
    this->showFullScreen();

    ui->titleLabel->setText(LoadString("IDS_SELFTEST_TITLE"));
    ui->cameraTitleLabel->setText(LoadString("IDS_CAMERA_TITLE"));
    ui->cameraValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->laserTitleLabel->setText(LoadString("IDS_LASER_TITLE"));
    ui->laserValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->batteryTitleLabel->setText(LoadString("IDS_BATTERY_TITLE"));
    ui->batteryValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->storageTitleLabel->setText(LoadString("IDS_STORAGE_TITLE"));
    ui->storageValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
    ui->versionLabel->setText(LoadString("IDS_VERSION"));

    startTimer(1000);
}

SelfTestWidget::~SelfTestWidget()
{
//    killTimer()
    delete ui;
}

void SelfTestWidget::timerEvent(QTimerEvent *event)
{
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
}
