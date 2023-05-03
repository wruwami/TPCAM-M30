#include "SelfTestDialog.h"
#include "ui_SelfTestDialog.h"

#include <QDate>
#include <QTime>
#include <QFile>
#include <QDebug>
#include <QByteArray>

#include "Color.h"
#include "StringLoader.h"
#include "BaseDialog.h"
#include "DateFormatManager.h"
#include "FileManager.h"

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

    QFile expired_file(GetPath("", SD) + "/" + ("expired_date.txt"));
    expired_file.open(QFile::ReadOnly);

    if (!expired_file.isOpen())
    {
        qDebug() << "no file has been opened";
        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
    }
    else
    {
        QByteArray ba = expired_file.readAll();
        QString str = QString(ba);
        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE") + GetDate(str));
    }
    expired_file.close();


    ui->versionLabel->setText(GetVersion() + "(" + GetDate(QDate::currentDate().toString("yyyyMMdd")) + ")");

    ui->expiredDateLabel->setStyleSheet("QLabel { color : red; }");
    ui->versionLabel->setStyleSheet("QLabel { color : #ffc000; }");

    // test
//    BaseDialog baseDialog(SelfTestWarningMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
//    baseDialog.exec();

    startTimer(1000);
    StartSelfTest();
}

SelfTestDialog::~SelfTestDialog()
{
//    killTimer()
    delete ui;
}

QString SelfTestDialog::GetVersion()
{
    QFile file(GetPath("", SD) + "/" + "verison_info.txt");
    file.open(QFile::ReadOnly);

    if (!file.isOpen())
    {
        qDebug() << "no file has been opened";
//        ui->versionLabel->setText(LoadString("IDS_EXPIRED_DATE"));
    }
    else
    {
        QByteArray ba = file.readAll();
        QString str = QString(ba);
        file.close();
        return str;
    }
    file.close();
    return "";
}

void SelfTestDialog::StartSelfTest()
{
    if (!CameraTest())
    {
        BaseDialog baseDialog(SelfTestWarningMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
        baseDialog.exec();
        return;
    }
    if (!LaserTest())
    {
        BaseDialog baseDialog(SelfTestWarningMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
        baseDialog.exec();
        return;
    }
    if (!BatteryTest())
    {
        BaseDialog baseDialog(SelfTestWarningMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
        baseDialog.exec();
        return;
    }
    if (!StorageTest())
    {
        BaseDialog baseDialog(SelfTestWarningMessageWidgetType, Qt::AlignmentFlag::AlignCenter);
        baseDialog.exec();
        return;
    }

}

bool SelfTestDialog::CameraTest()
{
    return true;
}

bool SelfTestDialog::LaserTest()
{
    return true;
}

bool SelfTestDialog::BatteryTest()
{
    return true;
}

bool SelfTestDialog::StorageTest()
{
    return true;
}

void SelfTestDialog::timerEvent(QTimerEvent *event)
{
    ui->dateTimeLabel->setText(GetDate(QDate::currentDate().toString("yyyyMMdd")) + " " + QTime::currentTime().toString("hh:mm:ss"));
//    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    m_nSecond++;
//    if (m_nSecond == 3)
//        accept();
//    else if (m_nSecond == 2)
//    {
//        ui->cameraValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
//        ui->laserValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
//        ui->batteryValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
//        ui->storageValueLabel->setText(LoadString("IDS_SELFTEST_SUCCESS"));
//    }
}
