#include "SelfTestDialog.h"
#include "ui_SelfTestDialog.h"
#include <QDate>
#include <QTime>
#include <QFile>

#include "Color.h"
#include "StringLoader.h"
#include "BaseDialog.h"

SelfTestDialog::SelfTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfTestDialog)
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
//    ui->cameraTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->cameraValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->laserTitleLabel->setText(LoadString("IDS_LASER_TITLE"));
//    ui->laserTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->laserValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->batteryTitleLabel->setText(LoadString("IDS_BATTERY_TITLE"));
//    ui->batteryTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->batteryValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->storageTitleLabel->setText(LoadString("IDS_STORAGE_TITLE"));
//    ui->storageTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->storageValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
    ui->versionLabel->setText(LoadString("IDS_VERSION"));


    ui->expiredDateLabel->setStyleSheet("QLabel { color : red; }");
    ui->versionLabel->setStyleSheet("QLabel { color : #ffc000; }");

    // test
//    BaseDialog baseDialog(SelfTestWarningMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
//    baseDialog.exec();

    startTimer(1000);
}

SelfTestDialog::~SelfTestDialog()
{
//    killTimer()
    delete ui;
}

void SelfTestDialog::timerEvent(QTimerEvent *event)
{
    ui->dateTimeLabel->setText(QDate::currentDate().toString("yyyy/MM/dd") + " " + QTime::currentTime().toString("hh:mm:ss"));
//    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    m_nSecond++;
    if (m_nSecond == 3)
        accept();
    else if (m_nSecond == 2)
    {
        ui->cameraValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
        ui->laserValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
        ui->batteryValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
        ui->storageValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
    }
}
