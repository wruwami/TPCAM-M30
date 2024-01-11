
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
#include "StorageManager.h"
#include "SerialViscaManager.h"
#include "SerialPacket.h"
#include "ViscaPacket.h"
#include "ConfigManager.h"

extern QString g_AppVersion;

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
    ui->titleLabel->setFontSize(23);
    ui->cameraTitleLabel->setText(LoadString("IDS_CAMERA_TITLE"));
    ui->cameraTitleLabel->setFontSize(23);
//    ui->cameraTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->cameraValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->cameraValueLabel->setFontSize(23);
    ui->laserTitleLabel->setText(LoadString("IDS_LASER_TITLE"));
    ui->laserTitleLabel->setFontSize(23);
//    ui->laserTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->laserValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->laserValueLabel->setFontSize(23);
    ui->batteryTitleLabel->setText(LoadString("IDS_BATTERY_TITLE"));
    ui->batteryTitleLabel->setFontSize(23);
//    ui->batteryTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->batteryValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->batteryValueLabel->setFontSize(23);
    ui->storageTitleLabel->setText(LoadString("IDS_STORAGE_TITLE"));
    ui->storageTitleLabel->setFontSize(23);
//    ui->storageTitleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->storageValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    ui->storageValueLabel->setFontSize(23);

    if (SerialGPSManager::GetInstance()->GetSatellitesInView() >= 3)
    {
        QDateTime datetime = SerialGPSManager::GetInstance()->GetDateTime();
        ;
        QString dateTimeString ("sudo date +%s -s @");
        dateTimeString.append(QString::number(datetime.toSecsSinceEpoch()));

        system(dateTimeString.toStdString().c_str());
    }

//    ui->titleLabel->setFontSize(18);
    qDebug() << GetPath("/settings", eMMC) + "/" + ("expired_date.txt");
    QFile expired_file(GetPath("/settings", eMMC) + "/" + ("expired_date.txt"));
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
        str.replace(" ", "");
        if(str.length() == 8)
        {
            ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE") + GetDate(str));
            ui->expiredDateLabel->setFontSize(23);
        }
        else
        {
        }
    }
    expired_file.close();

    QString build_date;
    QFile build_file(GetPath("/settings", eMMC) + "/" + ("build_date.txt"));
    build_file.open(QFile::ReadOnly);
    if (!build_file.isOpen())
    {
        qDebug() << "no file has been opened";
//        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
    }
    else
    {
        QByteArray ba = build_file.readAll();
        QString str = QString(ba);
        str.replace(" ", "");
        build_date = GetDate(str);
    }
    build_file.close();


    ui->versionLabel->setText(GetVersion() + " (" + build_date + ")");
    ui->versionLabel->setFontSize(23);

    ui->expiredDateLabel->setStyleSheet("QLabel { color : red; }");
    ui->versionLabel->setStyleSheet("QLabel { color : #ffc000; }");

    ui->dateTimeLabel->setText(GetDate(QDate::currentDate().toString("yyyyMMdd")) + " " + QTime::currentTime().toString("hh:mm:ss"));
    ui->dateTimeLabel->setFontSize(23);

    startTimer(1000);
    StartSelfTest();

//    while(1)
//    {
//        ui->dateTimeLabel->setText(GetDate(QDate::currentDate().toString("yyyyMMdd")) + " " + QTime::currentTime().toString("hh:mm:ss"));
//        m_nSecond++;
//        if (m_nSecond == 5)
//        {
//            if (m_nCamera == Status::Check)
//                m_nCamera = Status::Fail;
//            if (m_nLaser == Status::Check)
//                m_nLaser = Status::Fail;

//            break;
//        }

//        //qDebug() << /
//        SerialPacket* serial_packet = m_serialLaserManager.getLaser_packet();//->g_ReceiveData.header;
//        MsgFormat ReceiveData = serial_packet->g_ReceiveData;

////        qDebug() << ReceiveData.Header;
////        qDebug() << ReceiveData.Msg;
//        if (ReceiveData.Header == 0X05)
//            m_nLaser = Status::Pass;
//        else if (ReceiveData.Header == 0X00)
//            m_nLaser = Status::Check;
//        else
//            m_nLaser = Status::Fail;

//        ViscaPacket* visca_packet = m_serialViscaManager.getVisca_packet();
//        unsigned char send_data = visca_packet->send_header_data[0];
//        //cnrk
//        visca_packet->send_header_data.remove(0, 1);


//        if (send_data == 0X02)
//            m_nCamera = Status::Pass;
//        else if (send_data == 0)
//            m_nCamera = Status::Check;
//        else
//            m_nCamera = Status::Fail;

//        if (m_nCamera != Status::Check && m_nLaser != Status::Check && m_nBattery != Status::Check && m_nStorage != Status::Check)
//            break;
//        sleep(1);
//    }
}

SelfTestWidget::~SelfTestWidget()
{
//    m_serialLaserManager.close();
//    m_serialViscaManager.close();
//    killTimer()
    delete ui;
}

QString SelfTestWidget::GetVersion()
{
//    QFile file(GetPath("", SD) + "/" + "verison_info.txt");
//    file.open(QFile::ReadOnly);

//    if (!file.isOpen())
//    {
//        qDebug() << "no file has been opened";
////        ui->versionLabel->setText(LoadString("IDS_EXPIRED_DATE"));
//    }
//    else
//    {
//        QByteArray ba = file.readAll();
//        QString str = QString(ba);
//        file.close();
//        return str;
//    }
//    file.close();
    return g_AppVersion;
}

void SelfTestWidget::StartSelfTest()
{
    CameraTest();
//    if (CameraTest())
//    {
//        m_nCamera = Check;
//    }
//    else
//    {
//        m_nCamera = Fail;
//    }
    LaserTest();
//    if ()
//    {
//        m_nLaser = Check;
//    }
//    else
//    {
//        m_nLaser = Fail;
//    }
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

//    m_Timer = new QTimer;
//    m_Timer->start(5*1000);
//    connect(m_Timer, SIGNAL())
//    this->lower();



//    BaseDialog baseDialog(SelfTestWarningMessageWidgetType, isCamera, isLaser, isBattery, isStorage, Qt::AlignmentFlag::AlignCenter);
////    baseDialog.SetSelfTestResult();
//    if (baseDialog.exec() == QDialog::Accepted)
//        accept();
//    else
//        reject();

}

void SelfTestWidget::CameraTest()
{
    m_serialViscaManager.show_camera_model();
}

void SelfTestWidget::LaserTest()
{
    m_serialLaserManager.stop_laser();
    m_serialLaserManager.show_laser_info();
}

bool SelfTestWidget::BatteryTest()
{
    //get raw values
    ltc.getValues();

    //moving average filter
    ltc.filterValues();

    // load setting_battery.json
    ConfigManager config = ConfigManager("setting_battery.json");
    QJsonObject object = config.GetConfig();

    double dPowerOffVoltage = object["PowerOffVoltage"].toDouble();

    if (ltc.m_filteredVolt > dPowerOffVoltage)
        return true;

    return false;
}

bool SelfTestWidget::StorageTest()
{
    StorageManager sdcardManager;
    bool emmcresult = sdcardManager.GetEMMCExitSelfTest();
    bool sdresult = sdcardManager.GetSDExitSelfTest();
    if (emmcresult || sdresult)
        return false;
    return true;
}

Status SelfTestWidget::GetCamera()
{
    return m_nCamera;
}

Status SelfTestWidget::GetLaser()
{
    return m_nLaser;
}

Status SelfTestWidget::GetStorage()
{
    return m_nStorage;
}

Status SelfTestWidget::GetBattery()
{
    return m_nBattery;
}

void SelfTestWidget::timerEvent(QTimerEvent *event)
{
    ui->dateTimeLabel->setText(GetDate(QDate::currentDate().toString("yyyyMMdd")) + " " + QTime::currentTime().toString("hh:mm:ss"));
    m_nSecond++;
    if (m_nSecond == 5)
    {
        if (m_nCamera == Check)
            m_nCamera = Fail;
        if (m_nLaser == Check)
            m_nLaser = Fail;
        emit selftest_finished();
        killTimer(m_id);
//        close();
    }

    //qDebug() << /
    SerialPacket* serial_packet = m_serialLaserManager.getLaser_packet();//->g_ReceiveData.header;
    MsgFormat ReceiveData = serial_packet->g_ReceiveData;

    if (ReceiveData.Header == 0XE4)
    {
        m_nLaser = Status::Pass;
        ui->laserValueLabel->setText(LoadString("IDS_PASS"));
        ui->laserValueLabel->repaint();
    }
    else if (ReceiveData.Header == 0X00)
    {
        m_nLaser = Status::Check;
        ui->laserValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    }
//    else
//    {
//        m_nLaser = Status::Fail;
//        ui->laserValueLabel->setText(LoadString("IDS_FAIL"));
//    }

    ViscaPacket* visca_packet = m_serialViscaManager.getVisca_packet();
    send_data = visca_packet->send_data;

    if (send_data == 0X02)
    {
        m_nCamera = Status::Pass;
        ui->cameraValueLabel->setText(LoadString("IDS_PASS"));
        ui->cameraValueLabel->repaint();
    }
    else if (send_data == 0)
    {
        m_nCamera = Status::Check;
        ui->cameraValueLabel->setText(LoadString("IDS_SELFTEST_CHECK"));
    }
//    else
//    {
//        m_nCamera = Status::Fail;
//        ui->cameraValueLabel->setText(LoadString("IDS_FAIL"));
//    }

    if (m_nCamera != Status::Check && m_nLaser != Status::Check && m_nBattery != Status::Check && m_nStorage != Status::Check)
    {
        usleep(1000000);
        emit selftest_finished();
        killTimer(m_id);
    }
}
