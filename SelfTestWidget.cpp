#include "SelfTestWidget.h"
#include "ui_SelfTestWidget.h"

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
#include "SerialGPSManager.h"
#include "SerialLaserManager.h"
#include "SdcardManager.h"
#include "SerialViscaManager.h"
#include "SerialPacket.h"
#include "ViscaPacket.h"

SelfTestWidget::SelfTestWidget(QWidget *parent) :
    QWidget(parent),
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
//        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
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

    startTimer(1000);
    StartSelfTest();

    while(1)
    {
        ui->dateTimeLabel->setText(GetDate(QDate::currentDate().toString("yyyyMMdd")) + " " + QTime::currentTime().toString("hh:mm:ss"));
        m_nSecond++;
        if (m_nSecond == 5)
        {
            if (m_nCamera == Status::Check)
                m_nCamera = Status::Fail;
            if (m_nLaser == Status::Check)
                m_nLaser = Status::Fail;

            break;
        }

        //qDebug() << /
        SerialPacket* serial_packet = m_serialLaserManager.getLaser_packet();//->g_ReceiveData.header;
        MsgFormat ReceiveData = serial_packet->g_ReceiveData;

//        qDebug() << ReceiveData.Header;
//        qDebug() << ReceiveData.Msg;
        if (ReceiveData.Header == 0X05)
            m_nLaser = Status::Pass;
        else if (ReceiveData.Header == 0X00)
            m_nLaser = Status::Check;
        else
            m_nLaser = Status::Fail;

        ViscaPacket* visca_packet = m_serialViscaManager.getVisca_packet();
        unsigned char send_data = visca_packet->send_header_data[0];
        //cnrk
        visca_packet->send_header_data.remove(0, 1);


        if (send_data == 0X02)
            m_nCamera = Status::Pass;
        else if (send_data == 0)
            m_nCamera = Status::Check;
        else
            m_nCamera = Status::Fail;

        if (m_nCamera != Status::Check && m_nLaser != Status::Check && m_nBattery != Status::Check && m_nStorage != Status::Check)
            break;
        sleep(1);
    }
}

SelfTestWidget::~SelfTestWidget()
{
    m_serialLaserManager.close();
    m_serialViscaManager.close();
//    killTimer()
    delete ui;
}

QString SelfTestWidget::GetVersion()
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

void SelfTestWidget::StartSelfTest()
{
    if (CameraTest())
    {
        m_nCamera = Check;
    }
    else
    {
        m_nCamera = Fail;
    }
    if (LaserTest())
    {
        m_nLaser = Check;
    }
    else
    {
        m_nLaser = Fail;
    }
    if (BatteryTest())
    {
        ui->batteryValueLabel->setText(LoadString("IDS_PASS"));
        m_nBattery = Pass;
    }
    else
    {
        ui->batteryValueLabel->setText(LoadString("IDS_FAIL"));
        m_nBattery = Fail;
    }
    if (StorageTest())
    {
        ui->storageValueLabel->setText(LoadString("IDS_PASS"));
        m_nStorage = Pass;
    }
    else
    {
        ui->storageValueLabel->setText(LoadString("IDS_FAIL"));
        m_nStorage = Fail;
    }

//    this->lower();

    if (SerialGPSManager::GetInstance()->GetSatellitesInView() != 0)
    {
        QDateTime datetime = SerialGPSManager::GetInstance()->GetDateTime();
        QString string = datetime.toString("\"yyyy-MM-dd hh:mm:ss\"");
        QString dateTimeString ("date -s ");
        dateTimeString.append(string);

        system(dateTimeString.toStdString().c_str());

    }

//    BaseDialog baseDialog(SelfTestWarningMessageWidgetType, isCamera, isLaser, isBattery, isStorage, Qt::AlignmentFlag::AlignCenter);
////    baseDialog.SetSelfTestResult();
//    if (baseDialog.exec() == QDialog::Accepted)
//        accept();
//    else
//        reject();

}

bool SelfTestWidget::CameraTest()
{
    if (m_serialViscaManager.connectVisca() == "Connect")
    {
        m_serialViscaManager.show_camera_model();
        return true;
    }
    return false;
}

bool SelfTestWidget::LaserTest()
{
    if (m_serialLaserManager.connectLaser() == "Connect")
    {
        m_serialLaserManager.show_laser_info();
        return true;
    }
    return false;
}

bool SelfTestWidget::BatteryTest()
{
    //get raw values
    ltc.getValues();

    //moving average filter
    ltc.filterValues();

    if (ltc.m_filteredVolt > 9.4)
        return true;

    return false;
}

bool SelfTestWidget::StorageTest()
{
    SdcardManager sdcardManager;
    if (sdcardManager.isExistEMMccard == true && sdcardManager.isExistEMMccard == true)
    {
        float sdpercent = sdcardManager.GetSDAvailable() / sdcardManager.GetSDTotal();
        float emmcpercent = sdcardManager.GeteMMCAvailable() / sdcardManager.GeteMMCTotal();
        if (sdpercent > 0.8 && emmcpercent > 0.8)
            return true;
    }

    return false;
}

void SelfTestWidget::timerEvent(QTimerEvent *event)
{
    ui->dateTimeLabel->setText(GetDate(QDate::currentDate().toString("yyyyMMdd")) + " " + QTime::currentTime().toString("hh:mm:ss"));
//    m_nSecond++;

    //qDebug() << /
    SerialPacket* serial_packet = m_serialLaserManager.getLaser_packet();//->g_ReceiveData.header;
    MsgFormat ReceiveData = serial_packet->g_ReceiveData;

    qDebug() << ReceiveData.Header;
    qDebug() << ReceiveData.Msg;

    ViscaPacket* visca_packet = m_serialViscaManager.getVisca_packet();
    qDebug() << visca_packet->g_RxBuf;

    if (m_nCamera != Status::Check && m_nLaser != Status::Check && m_nBattery != Status::Check && m_nStorage != Status::Check)
        this->close();

}
