#include "EnforcementComponentWidget.h"
#include "ui_EnforcementComponentWidget.h"

#include <QPainter>
#include <QTime>

#include "StringLoader.h"
#include "WidgetSize.h"
#include "SerialLaserManager.h"
#include "SerialPacket.h"
#include "SpeedUnitManager.h"
#include "WidgetSize.h"
#include "SerialViscaManager.h"
#include "StorageManager.h"
#include "HeadUpDisplay.h"
#include "HUDManager.h"
#include "BaseDialog.h"
#include "Logger.h"
#include "FtpTransThread.h"

using namespace TPCAM_M30;

extern int g_nCrackDownIndex;
#define TRIGGER_FILE "/sys/class/gpio/gpio110/value"
//#define TRIGGER_FILE "a.txt"

#define DEBUG_MODE 0

EnforcementComponentWidget::EnforcementComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementComponentWidget)
{
    ui->setupUi(this);

//    SetCamera();

    m_object = m_config.GetConfig();
    m_object2 = m_config2.GetConfig();

    ui->hidePushButton->setText(LoadString("IDS_HIDE"));
    ui->hidePushButton->setFontSize(20);
    ui->readyPushButton->setText(LoadString("IDS_READY"));
    ui->readyPushButton->setFontSize(20);
//    ui->zoomRangePushButton->setText("Z: 100~160 m");
    ui->dzPlusPushButton->setText(LoadString("IDS_DZ_PLUS"));
    ui->dzPlusPushButton->setFontSize(20);
    ui->dzMinusPushButton->setText(LoadString("IDS_DZ_MINUS"));
    ui->dzMinusPushButton->setFontSize(20);

    ui->saveImagePushButton->setText(LoadString("IDS_SAVE_IMAGE1") + '\n' + LoadString("IDS_SAVE_IMAGE2"));
    ui->saveImagePushButton->setFontSize(20);
    ui->truckPushButton->setImage("enforcement", "truck.jpg");
    ui->truckPushButton->setCheckable(true);
    ui->bikePushButton->setImage("enforcement", "bike.jpg");
    ui->bikePushButton->setCheckable(true);

//    m_pReadyButton = ui->readyPushButton;

    m_captureSpeed = m_object["capture speed"].toArray();

    /*QString speedLimit = QString("CS: %0%4\nT: %2%4\nM: %3%4").arg(QString::number(m_captureSpeed[0].toInt())).arg(QString::number(m_captureSpeed[1].toInt())).arg(QString::number(m_captureSpeed[2].toInt())).arg(speedUnitValue());
    ui->speedLimitLabel->setText(speedLimit);
    ui->speedLimitLabel->setFontSize(14);
    ui->speedLimitLabel->setDisabled(true);*/

    DisplaySpeedLimit();

    ui->recIconLabel->setFontSize(30);
    ui->recLabel->setFontSize(30);
    ui->speedLabel->setFontSize(30);

//    m_pDistanceLabel = new CustomLabel;
    m_pDistanceLabel = new CustomLabel(this);
    m_pDistanceLabel->setStyleSheet("color: white; background: transparent;");
    m_pDistanceLabel->setAlignment(Qt::AlignCenter);
    m_pDistanceLabel->setGeometry(GetWidgetSizePos(QRect(QPoint(464,595-125), QSize(678, 115))));
    m_pDistanceLabel->setFontSize(30);

//    ui->distanceLabel->setFontSize(30);
//    ui->distanceLabel->setAlignment(Qt::AlignCenter);

    m_SpeedLimit = m_object["speed limit"].toArray();

    if (m_object["speed selection"].toInt() == 1)
        m_UserModeOn = true;
    else
        m_UserModeOn = false;

    switch(m_object["enforcement selection"].toInt())
    {
    case 1:
    {
        m_nEnforcementMode = I;
    }
        break;
    case 2:
    {
        m_nEnforcementMode = A;
    }
        break;
    case 3:
    {
        m_nEnforcementMode = V;
    }
        break;
    }

    m_nZoomIndex = ConfigManager("parameter_enforcement.json").GetConfig()["zoom index"].toInt() - 1;

    ConfigManager con = ConfigManager("parameter_setting3.json");
    QJsonObject object = con.GetConfig();

    QSizePolicy sp_retain = QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    sp_retain.setRetainSizeWhenHidden(true);

    QSizePolicy sp_retain_label = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sp_retain_label.setRetainSizeWhenHidden(true);

    ui->hidePushButton->setSizePolicy(sp_retain);
    ui->readyPushButton->setSizePolicy(sp_retain);
    ui->zoomRangePushButton->setSizePolicy(sp_retain);
    ui->dzPlusPushButton->setSizePolicy(sp_retain);
    ui->dzMinusPushButton->setSizePolicy(sp_retain);

    ui->saveImagePushButton->setSizePolicy(sp_retain);
    ui->truckPushButton->setSizePolicy(sp_retain);
    ui->bikePushButton->setSizePolicy(sp_retain);

    ui->speedLimitLabel->setSizePolicy(sp_retain_label);

    ui->enforcementCountLabel->setSizePolicy(sp_retain_label);
    ui->enforcementDistanceSpeedLabel->setSizePolicy(sp_retain);
    ui->enforcementTimeLabel->setSizePolicy(sp_retain_label);
    ui->recIconLabel->setSizePolicy(sp_retain_label);
    ui->recLabel->setSizePolicy(sp_retain_label);
    ui->speedLabel->setSizePolicy(sp_retain);
    ui->thumbnailLabel->setSizePolicy(sp_retain_label);

//    camInit();
    hudInit();
//    laserInit();
    initRec();

    ConfigManager config = ConfigManager("zoom_level.json");
    object = config.GetConfig();


    QJsonArray ar;
    ar = object["st mode meter dist"].toArray();
    foreach(auto item, ar)
    {
        m_stmetervector.push_back(item.toString());
    }
    ar = object["st mode feet dist"].toArray();
    foreach(auto item, ar)
    {
        m_stfeetvector.push_back(item.toString());
    }
    ar = object["lt mode meter dist"].toArray();
    foreach(auto item, ar)
    {
        m_ltmetervector.push_back(item.toString());
    }
    ar = object["lt mode feet dist"].toArray();
    foreach(auto item, ar)
    {
        m_ltfeetvector.push_back(item.toString());
    }
    if (m_UserModeOn)
    {
        if (distance() == meter)
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_stmetervector[m_nZoomIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
        else
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_stfeetvector[m_nZoomIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
    }
    else
    {
        if (m_nZoomIndex > 4)
            m_nZoomIndex = 4;
        if (distance() == meter)
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_ltmetervector[m_nZoomIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
        else
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_ltfeetvector[m_nZoomIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
    }
    if(m_nEnforcementMode == V)
    {
        ui->zoomRangePushButton->setText("Z: AUTO");
//        doVMode();
    }

    int x = ConfigManager("setting_reticle.json").GetConfig()["Camera reticle pos"].toArray()[0].toInt();
    int y = ConfigManager("setting_reticle.json").GetConfig()["Camera reticle pos"].toArray()[1].toInt();
    m_cross.setX(x - Laser_x);
    m_cross.setY(y - Laser_y);

    startTimer(1000);

    m_nVModeSecond = ConfigManager("video_mode.json").GetConfig()["recoding minute"].toInt() * 60;
    connect(&m_VModeTimer, SIGNAL(timeout()), this, SLOT(VModeVideoSave()));
    //    connect(&m_WhiteClearTimer, SIGNAL(timeout), this, SLOT(ClearDisplay()));
    connect(&m_WhiteSpeedClearTimer, SIGNAL(timeout()), this, SLOT(ClearSpeedDisplay()));
    connect(&m_WhiteDistanceClearTimer, SIGNAL(timeout()), this, SLOT(ClearDistanceDisplay()));
//    connect(&m_ManualModeTimer, SIGNAL(timeout()), this, SLOT(on_ManualMode()));

    doEnforceMode(false);

    QJsonObject jsonObject = ConfigManager("parameter_setting6.json").GetConfig();
    if (jsonObject["ftp select"].toInt() == 3)
    {
//        m_mutex.reset(new QMutex);
//        m_FileQueue.reset(new QQueue<QString>);
        m_pFtpThread = new FtpTransThread;
        connect(m_pFtpThread, &FtpTransThread::finished, m_pFtpThread, &QObject::deleteLater);
        connect(m_pFtpThread, SIGNAL(finished()), this, SLOT(closeThread()));
        connect(this, SIGNAL(push_file(QString)), m_pFtpThread, SLOT(on_push_file(QString)));


        m_pFtpThread->start();
    }

    connect(v4l2_thread::getInstance(), SIGNAL(saveImage()), this, SLOT(on_saveImage()));

    connect(&m_ManualTimer, SIGNAL(timeout()), this, SLOT(do_FileSystemWatcherTimer()));

    snapshotSound = new SoundPlayer("snapshot.raw");
//    int nSelDayNight = m_object2["day&night selection"].toInt();
//    if( 0 < nSelDayNight && nSelDayNight < 4)
//    {
//        v4l2_thread::getInstance()->setUseFlash(false);
//    }
//    else
//    {
//        v4l2_thread::getInstance()->setUseFlash(true);
//    }

//    ConfigManager config = ConfigManager("parameter_setting6.json");
//    QJsonObject jsonObject = config.GetConfig();

//    if (jsonObject["ftp select"].toInt() == 3)
//    {

//    }
//    m_pFtpThread.reset(new FtpTransThread);
//    QObject::connect(m_pFtpThread.data(), &FtpTransThread::finished, m_pFtpThread.data(), &QObject::deleteLater);
//    m_pFtpThread->start();
//    m_pSerialLaserManager->show_laser_info();
#if DEBUG_MODE
    SaveImageVideo();
#endif
//    switch (m_nMode)
//    {
//    case Ready:
//    {
//        ui->readyPushButton->setText(LoadString("IDS_Ready"));
//        m_nMode = Ready;
//        doReadyMode();
//    }
//        break;
//    case AT:
//    {
//        ui->readyPushButton->setText(LoadString("IDS_AT"));
//        m_nMode = AT;
//        doATMode();

//    }
//        break;
//    case Manual:
//    {
//        ui->readyPushButton->setText(LoadString("IDS_Manual"));
//        m_nMode = Manual;
//        doManualMode();
//    }
//        break;
//    }
//    m_pSerialLaserManager->getLaser_packet();
//    connect(m_p)
}

EnforcementComponentWidget::~EnforcementComponentWidget()
{
    delete snapshotSound;

    doReadyMode();

    doVModeTimer(false);

    doEnforceMode(false);

//    if (m_pFtpThread)
//    {
//        delete m_pFtpThread;
//        m_pFtpThread = nullptr;
//    }
//    if (\\m_bFtpMode && m_pFtpThread->isRunning())
//    {
//        m_pFtpThread->requestInterruption();
//        sleep(1);
//        m_pFtpThread->exit();
//        m_pFtpThread->wait();
//    }

//    m_pFtpThread->requestInterruption();
//    emit ShowRedOutLine(false);
//    if (m_pCamera)
//    {
//        delete m_pCamera;
//        m_pCamera = nullptr;
//    }
    delete ui;
}

void EnforcementComponentWidget::dzPlus()
{
//    SerialViscaManager serialViscaManager;
    m_pSerialViscaManager->plus_dzoom();
    SaveDZoomJson();
//    if (m_UserModeOn)
//    {
//        if (m_nDistance == meter)
//        {
//            if (m_nStIndex < m_stmetervector.size() - 1)
//            {
//                m_nStIndex++;
//                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stmetervector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
//                SerialViscaManager serialViscaManager;
//                serialViscaManager.dzoom(m_nStIndex);
//            }
//        }
//        else
//        {
//            if (m_nStIndex < m_stfeetvector.size() - 1)
//            {
//                m_nStIndex++;
//                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stfeetvector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
//                SerialViscaManager serialViscaManager;
//                serialViscaManager.dzoom(m_nStIndex);
//            }

//        }
//    }
//    else
//    {
//        if (m_nDistance == meter)
//        {
//            if (m_nLtIndex < m_ltmetervector.size() - 1)
//            {
//                m_nLtIndex++;
//                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltmetervector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
//                SerialViscaManager serialViscaManager;
//                serialViscaManager.dzoom(m_nLtIndex);
//            }

//        }
//        else
//        {
//            if (m_nLtIndex < m_ltfeetvector.size() - 1)
//            {
//                m_nLtIndex++;
//                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltfeetvector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
//                SerialViscaManager serialViscaManager;
//                serialViscaManager.dzoom(m_nLtIndex);
//            }

//        }
//    }
}
void EnforcementComponentWidget::dzMinus()
{
//    SerialViscaManager serialViscaManager;
    m_pSerialViscaManager->minus_dzoom();//    if (m_UserModeOn)
    SaveDZoomJson();
//    {
//        if (m_nStIndex != 0)
//        {
//            m_nStIndex--;
//            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stmetervector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
//            SerialViscaManager serialViscaManager;
//            serialViscaManager.dzoom(m_nStIndex);
//        }
//    }
//    else
//    {
//        if (m_nLtIndex != 0)
//        {
//            m_nLtIndex--;
//            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltmetervector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
//            SerialViscaManager serialViscaManager;
//            serialViscaManager.dzoom(m_nLtIndex);
//        }
//    }

}

void EnforcementComponentWidget::SaveImageVideo()
{
    QJsonObject object = m_config.GetConfig();
    stEnforcementInfo enforceInfo;
    enforceInfo.nCaptureSpeed = (int)m_fSpeed;
    enforceInfo.nSpeedLimit = m_SpeedLimit[m_nVehicleMode].toInt();
    enforceInfo.nCaptureSpeedLimit = m_captureSpeed[m_nVehicleMode].toInt();
    enforceInfo.nDistance = (int)m_fDistance;
    enforceInfo.bUserMode = m_UserModeOn;
    enforceInfo.enforceMode = m_nEnforcementMode;
    enforceInfo.vehicle = m_nVehicleMode;
    enforceInfo.zoom_index = m_nZoomIndex;
    QDateTime datetime = QDateTime::currentDateTime();
    enforceInfo.date = datetime.toString("yyyyMMdd");
    enforceInfo.time = QString(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]);

//    QString qstrFilename = ;
//    QString qstrPath = ;

//    switch(object["enforcement selection"].toInt())
    switch(m_nEnforcementMode)
    {
    case I:
    {
        m_pCamera->SaveImage(AI, enforceInfo, SNAPSHOT);
        if (m_pFtpThread)
        {
//            PushFile(GETSDPATH(SNAPSHOT) + "/" + GetFileName(AI, enforceInfo));
            //            emit push_file(GETSDPATH(SNAPSHOT) + "/" + GetFileName(AI, enforceInfo));
                        m_pFtpThread->PushFile(GETSDPATH(SNAPSHOT) + "/" + GetFileName(AI, enforceInfo));

        }

    }
        break;
    case A:
    {
        m_pCamera->SaveImage(AI, enforceInfo, SNAPSHOT);
        if (m_pFtpThread)
        {
//            PushFile(GETSDPATH(SNAPSHOT) + "/" + GetFileName(AI, enforceInfo));
//            emit push_file(GETSDPATH(SNAPSHOT) + "/" + GetFileName(AI, enforceInfo));
            m_pFtpThread->PushFile(GETSDPATH(SNAPSHOT) + "/" + GetFileName(AI, enforceInfo));
        }
        m_pCamera->SaveVideo(AV, enforceInfo, AUTO);
        if (m_pFtpThread)
        {
//            PushFile(GETSDPATH(AUTO) + "/" + GetFileName(AV, enforceInfo));
            emit push_file(GETSDPATH(AUTO) + "/" + GetFileName(AV, enforceInfo));
            m_pFtpThread->PushFile(GETSDPATH(AUTO) + "/" + GetFileName(AV, enforceInfo));
        }

    }
        break;
    case V:
    {
        m_pCamera->SaveVideo(VV, enforceInfo, VIDEO);
        if (m_pFtpThread)
        {
//            PushFile(GETSDPATH(VIDEO) + "/" + GetFileName(VV, enforceInfo));
//            emit push_file(GETSDPATH(VIDEO) + "/" + GetFileName(VV, enforceInfo));
            m_pFtpThread->PushFile(GETSDPATH(VIDEO) + "/" + GetFileName(VV, enforceInfo));
        }
    }
        break;
    }
}

//void EnforcementComponentWidget::SaveVideo()
//{
//    stEnforcementInfo enforceInfo;
//    //
//    m_pCamera->SaveVideo(enforceInfo);
//}

void EnforcementComponentWidget::SaveImage()
{
    stEnforcementInfo enforceInfo;
    enforceInfo.nCaptureSpeed = (int)0;
    enforceInfo.nSpeedLimit = m_SpeedLimit[m_nVehicleMode].toInt();
    enforceInfo.nCaptureSpeedLimit = m_captureSpeed[m_nVehicleMode].toInt();
    enforceInfo.nDistance = (int)m_fDistance;
    enforceInfo.bUserMode = m_UserModeOn;
    enforceInfo.enforceMode = m_nEnforcementMode;
    enforceInfo.vehicle = m_nVehicleMode;
    enforceInfo.zoom_index = m_nZoomIndex;
    QDateTime datetime = QDateTime::currentDateTime();
    enforceInfo.date = datetime.toString("yyyyMMdd");
    enforceInfo.time = QString(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]);
//    QPixmap pixmap = m_pCamera->grab();
//    pixmap.save(GETSDPATH(MANUAL_CAPTURE) + "/" +GetFileName(MC, enforceInfo));
    m_pCamera->SaveImage(MC, enforceInfo, MANUAL_CAPTURE);
}


void EnforcementComponentWidget::on_hidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->hidePushButton->setText(LoadString("IDS_SHOW"));
        hide(false);
    }
    else
    {
        ui->hidePushButton->setText(LoadString("IDS_HIDE"));
        show(false);
    }
}

//void EnforcementComponentWidget::doShartAction()
//{

//}

void EnforcementComponentWidget::hide(bool bAll)
{
    if (bAll)
        ui->hidePushButton->hide();
    ui->readyPushButton->hide();
    ui->zoomRangePushButton->hide();
    ui->dzPlusPushButton->hide();
    ui->dzMinusPushButton->hide();

    ui->saveImagePushButton->hide();
    ui->truckPushButton->hide();
    ui->bikePushButton->hide();

    ui->speedLimitLabel->hide();

    ui->enforcementCountLabel->hide();
    ui->enforcementDistanceSpeedLabel->hide();
    ui->enforcementTimeLabel->hide();
    ui->thumbnailLabel->hide();
    m_pDistanceLabel->hide();
}

void EnforcementComponentWidget::show(bool bAll)
{
    if (bAll)
        ui->hidePushButton->show();
    ui->readyPushButton->show();
    ui->zoomRangePushButton->show();
    ui->dzPlusPushButton->show();
    ui->dzMinusPushButton->show();

    ui->saveImagePushButton->show();
    ui->truckPushButton->show();
    ui->bikePushButton->show();

    ui->speedLimitLabel->show();

    ui->enforcementCountLabel->show();
    ui->enforcementDistanceSpeedLabel->show();
    ui->enforcementTimeLabel->show();
    ui->thumbnailLabel->show();
    m_pDistanceLabel->show();
}

void EnforcementComponentWidget::SetCamera()
{
//     m_pCamera = new Camera(this);
//     m_pCamera->setGeometry(GetWidgetSizePos(QRect(0, 0, 1600, 960)));

//     qDebug() << m_pCamera->geometry();
//     m_pCamera->lower();
//     m_pCamera->show();
}

void EnforcementComponentWidget::camInit()
{

    m_pSerialViscaManager->set_IRCorrection_standard();
    m_pSerialViscaManager->set_AE_Mode("03");

    m_pSerialViscaManager->SetDayMode(m_object2["day&night selection"].toInt());

    m_pSerialViscaManager->set_manual_focus();
//    m_pSerialViscaManager.set_AE_mode2e();
    m_pSerialViscaManager->separate_zoom_mode();

//    Config
    QJsonObject object = ConfigManager("parameter_enforcement.json").GetConfig();
    m_nZoomIndex = object["zoom index"].toInt() - 1;
    m_pSerialViscaManager->SetZoom(m_nZoomIndex);
    m_pSerialViscaManager->SetFocus(m_nZoomIndex);
    m_pSerialViscaManager->SetDZoom(m_nZoomIndex);

//    m_pSerialViscaManager->dzoom_from_pq("00");

//    ConfigManager config = ConfigManager("parameter_enforcement.json");
//    QJsonObject object = config.GetConfig();

}

void EnforcementComponentWidget::hudInit()
{
    m_hudManager.HUDEnforcementInit();
//    ConfigManager config2 = ConfigManager("parameter_reticle.json");
//    QJsonObject object2 = config2.GetConfig();
//    QJsonArray array = object2["HUD reticle pos"].toArray();
//    m_hudManager.SetPointX(array[0].toInt());
//    m_hudManager.SetPointY(array[1].toInt());

//    m_hudManager.ShowDistanceUnit(true);

//    m_hudManager.hud().changeToSpeedCheckMode();


    //hudManager.SetReticleShape()
}

void EnforcementComponentWidget::hudClear()
{
    m_hudManager.HUDEnforcementInit();
}

void EnforcementComponentWidget::laserInit()
{
//     if (m_pSerialLaserManager == nullptr)
//        m_pSerialLaserManager = new SerialLaserManager;
    ConfigManager config = ConfigManager("parameter_setting1.json");
    QJsonObject object = config.GetConfig();
    ConfigManager config2 = ConfigManager("parameter_setting2.json");
    QJsonObject object2 = config2.GetConfig();

    if (object2["weather selection"].toInt() == 1)
        m_pSerialLaserManager->set_weather_mode(0);
    else
        m_pSerialLaserManager->set_weather_mode(1);

    if (object2["anti-jamming selection"].toInt() == 1)
        m_pSerialLaserManager->set_AJamming_mode(1);
    else
        m_pSerialLaserManager->set_AJamming_mode(0);

    if (object2["buzzer selection"].toInt() == 1)
        m_pSerialLaserManager->set_buzzer_mode(1);
    else
        m_pSerialLaserManager->set_buzzer_mode(0);

    if(m_nEnforcementMode == V)
    {
        int dn = object2["day&night selection"].toInt();
        m_pSerialLaserManager->set_night_mode(0); //V mode not require night mode
        m_bNight = false;
        m_pSerialLaserManager->set_speed_measure_mode(1);

        ui->zoomRangePushButton->setText("Z: AUTO");
        doVMode();
        return;
    }

    ConfigManager config3 = ConfigManager("parameter_enforcement.json");
    QJsonObject object3 = config3.GetConfig();

    int zoom_index = object3["zoom index"].toInt();

    SetLaserDetectionAreaDistance(zoom_index);

    int dn = object2["day&night selection"].toInt();
    if (dn >= 0 && dn <=3)
    {
        m_pSerialLaserManager->set_night_mode(0);
        m_bNight = false;
    }
    else
    {
        m_pSerialLaserManager->set_night_mode(1);
        m_bNight = true;
    }
    m_pSerialLaserManager->set_speed_measure_mode(1);
}

void EnforcementComponentWidget::SetCamera(Camera *camera)
{
    if (camera != nullptr)
        m_pCamera = camera;
}

void EnforcementComponentWidget::setMainMenuSize(QSize size)
{
    m_MainMenuWidgetSize = size;
}

void EnforcementComponentWidget::doATMode()
{
//    emit sig_ATmodeOn();
//    emit ShowRedOutLine(true);
    m_pDistanceLabel->show();
    hudClear();

//    m_pSerialLaserManager->stop_laser();
//    m_pSerialLaserManager->request_distance(false);

    if (m_nEnforcementMode == V)
    {
        doVModeTimer(true);
//        return;
    }

    SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
    m_pSerialLaserManager->start_laser();
    m_pSerialLaserManager->request_distance(true);
    if (m_bVirtualMode)
        m_pSerialLaserManager->start_virtualSpeed();
    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), this, SLOT(on_showCaptureSpeedDistance(float,float, int)));
    connect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), this, SLOT(on_showSpeedDistance(float,float)));
    connect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float, int)));
//    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), &m_hudManager.hud(), SLOT(showCaptureSpeedDistance(float, float, int)));
//    connect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), &m_hudManager.hud(), SLOT(showSpeedDistanceSensitivity(float, float)));
//    connect(laser_packet, SIGNAL(sig_showDistance(float,int)), &m_hudManager.hud(), SLOT(showDistanceSensitivity(float, int)));

    SetLogMsg(BUTTON_CLICKED, "AT_MODE");
}

//void EnforcementComponentWidget::doManualMode()
//{

////    displayRedOutline(false);
////
////    if (m_triggerStatus == PRESS)
////        doATMode();
////    else
////        doReadyMode();
////    m_ManualModeTimer.start(1);
////    // release
////
//}

void EnforcementComponentWidget::doReadyMode()
{
    emit sig_ATmodeOff();
    m_pDistanceLabel->hide();
    m_WhiteSpeedClearTimer.stop();//prevent from being RED when entering Vmode

    doEnforceMode(false);
    doVModeTimer(false);
    SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();

    m_pSerialLaserManager->stop_laser();
    m_pSerialLaserManager->stop_virtualSpeed();
    m_pSerialLaserManager->request_distance(false);
    m_hudManager.HUDClear();

    disconnect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), this, SLOT(on_showCaptureSpeedDistance(float,float, int)));
    disconnect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), this, SLOT(on_showSpeedDistance(float,float)));
    disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float, int)));
    disconnect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), &m_hudManager.hud(), SLOT(showCaptureSpeedDistance(float, float, int)));
    disconnect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), &m_hudManager.hud(), SLOT(showSpeedDistanceSensitivity(float, float)));
    disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), &m_hudManager.hud(), SLOT(showDistanceSensitivity(float, int)));

    SetLogMsg(BUTTON_CLICKED, "READY_MODE");
}

float EnforcementComponentWidget::GetCaptureSpeedLimit()
{
    switch (m_nVehicleMode)
    {
    case Normal:
    {
        return (float)(m_captureSpeed.at(0).toDouble());
    }
        break;
    case Truck:
    {
        return (float)(m_captureSpeed.at(1).toDouble());
    }
        break;
    case MotoCycle:
    {
        return (float)(m_captureSpeed.at(2).toDouble());
    }
        break;
    }
}

void EnforcementComponentWidget::initStyle()
{

}

void EnforcementComponentWidget::displaySpeedDistance(float fSpeed, float fDistance, QColor color, bool nRec)
{
    m_pDistanceLabel->setColor(color);
    m_pDistanceLabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distanceValue());
    // REC
    ui->speedLabel->setColor(color);
    ui->speedLabel->setText(QString::number(getSpeedValue(fSpeed))+speedUnitValue());
//    if (nRec)
//    {
//        ui->recLabel->show();
//        ui->recIconLabel->show();
//    }
//    else
//    {
//        if (m_nEnforcementMode == V)
//        {
//            ui->recLabel->show();
//            ui->recIconLabel->show();
//        }
//        else
//        {
//            ui->recLabel->hide();
//            ui->recIconLabel->hide();
//        }

//    }
//    if (m_nEnforcementMode != V)
//        QTimer::singleShot(500, this, SLOT(StopDisPlayRec()));
}

void EnforcementComponentWidget::displayDistance(float fDistance)
{
    m_pDistanceLabel->setColor(Qt::white);
    if(fDistance >= 9999.0)
        m_pDistanceLabel->setText("----.-" + distanceValue());
    else
        m_pDistanceLabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distanceValue());

    ui->speedLabel->setText("");
}

void EnforcementComponentWidget::displayRedOutline(bool nOn)
{
    if (nOn)
    {
        m_bRedLine = true;
        emit ShowRedOutLine(true);
    }
    else
    {
        m_bRedLine = false;
        emit ShowRedOutLine(false);
    }
}

void EnforcementComponentWidget::displayThumbnailSpeedDistance(float fSpeed, float fDistance)
{
    ui->enforcementCountLabel->setText(QString::number(g_nCrackDownIndex++));
    ui->enforcementTimeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    ui->enforcementDistanceSpeedLabel->setText(QString::number(getDistanceValue(fDistance)) + distanceValue() + ", " + QString::number(getSpeedValue(fSpeed)) + speedUnitValue());
}

void EnforcementComponentWidget::displayThumbnail()
{
    QPixmap pixmap = m_pCamera->grab();
    ui->thumbnailLabel->setPixmap(pixmap.scaled(ui->thumbnailLabel->width(), ui->thumbnailLabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void EnforcementComponentWidget::displayHudSpeedDistance(bool nDisplay, bool nSpeed, bool nRec, bool nUnit)
{
    m_hudManager.ShowSpeed(nSpeed, nRec);
    QTimer::singleShot(500, this, SLOT(StopHUDRec()));
    m_hudManager.ShowDistance(nDisplay);
    m_hudManager.ShowDistanceUnit(nUnit);
}

void EnforcementComponentWidget::displayHudDistance(bool nDisplay, bool nUnit)
{
    m_hudManager.ShowDistance(nDisplay);
    m_hudManager.ShowDistanceUnit(nUnit);
}

void EnforcementComponentWidget::SetLaserDetectionAreaDistance(int zoom_index)
{
    int distance = 0, area = 0;
    switch (zoom_index)
    {
    case 1:
    {
        if (m_UserModeOn)
        {
            distance = 20;
            area = 3;
        }
        else
        {
            distance = 18;
            area = 18;
        }
    }
        break;
    case 2:
    {
        if (m_UserModeOn)
        {
            distance = 40;
            area = 3;
        }
        else
        {
            distance = 48;
            area = 12;
        }

    }
        break;
    case 3:
    {
        if (m_UserModeOn)
        {
            distance = 60;
            area = 3;
        }
        else
        {
            distance = 80;
            area = 20;
        }

    }
        break;
    case 4:
    {
        if (m_UserModeOn)
        {
            distance = 80;
            area = 3;
        }
        else
        {
            distance = 130;
            area = 30;
        }

    }
        break;
    case 5:
    {
        if (m_UserModeOn)
        {
            distance = 100;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 6:
    {
        if (m_UserModeOn)
        {
            distance = 120;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 7:
    {
        if (m_UserModeOn)
        {
            distance = 140;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 8:
    {
        if (m_UserModeOn)
        {
            distance = 160;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 9:
    {
        if (m_UserModeOn)
        {
            distance = 180;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    case 10:
    {
        if (m_UserModeOn)
        {
            distance = 200;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    case 11:
    {
        if (m_UserModeOn)
        {
            distance = 220;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    case 12:
    {
        if (m_UserModeOn)
        {
            distance = 240;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;

    case 13:
    {
        if (m_UserModeOn)
        {
            distance = 260;
            area = 3;
        }
        else
        {
            distance = 1580;
            area = 1420;
        }

    }
        break;
    }

    m_pSerialLaserManager->set_detection_distance(distance);
    m_pSerialLaserManager->set_detection_area(area);
}

void EnforcementComponentWidget::zoomRange()
{
    if(m_nEnforcementMode == V)
        return;
     disconnect(m_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(doVModeZFControl(float, int)) );
//    int zoom_index = 0;
    if (m_UserModeOn)
    {
        m_nZoomIndex++;
        if (m_nZoomIndex >= m_stmetervector.size())
            m_nZoomIndex = 0;

//        zoom_index = m_nZoomIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_stmetervector[m_nZoomIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_stfeetvector[m_nZoomIndex]+distanceValue());
        }
    }
    else
    {
        m_nZoomIndex++;
        if (m_nZoomIndex >= m_ltmetervector.size())
            m_nZoomIndex = 0;

//        zoom_index = m_nZoomIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_ltmetervector[m_nZoomIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_ltfeetvector[m_nZoomIndex]+distanceValue());
        }
    }

    qDebug() << "zoom_index" << m_nZoomIndex;
    m_pSerialViscaManager->SetZoom(m_nZoomIndex);
    m_pSerialViscaManager->SetFocus(m_nZoomIndex);
    m_pSerialViscaManager->SetDZoom(m_nZoomIndex);

    SetLogMsg(BUTTON_CLICKED, "ZOOM_INDEX, " + ui->zoomRangePushButton->text());
    ConfigManager con = ConfigManager("parameter_enforcement.json");
    QJsonObject object = con.GetConfig();
    object["zoom index"] = (int)m_nZoomIndex + 1;
    con.SetConfig(object);
    con.SaveFile();

    SetLaserDetectionAreaDistance(m_nZoomIndex + 1);
}

void EnforcementComponentWidget::zoomRangeMinus()
{
    if(m_nEnforcementMode == V)
        return;
    disconnect(m_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(doVModeZFControl(float, int)) );
    //    int zoom_index = 0;
    if (m_UserModeOn)
    {
        m_nZoomIndex--;
        if (m_nZoomIndex <= 0)
            m_nZoomIndex = m_stmetervector.size() - 1;

        //        zoom_index = m_nZoomIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_stmetervector[m_nZoomIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_stfeetvector[m_nZoomIndex]+distanceValue());
        }
    }
    else
    {
        m_nZoomIndex--;
        if (m_nZoomIndex <= 0)
            m_nZoomIndex = m_ltmetervector.size() - 1;

        //        zoom_index = m_nZoomIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_ltmetervector[m_nZoomIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_ltfeetvector[m_nZoomIndex]+distanceValue());
        }
    }

    qDebug() << "zoom_index" << m_nZoomIndex;
    m_pSerialViscaManager->SetZoom(m_nZoomIndex);
    m_pSerialViscaManager->SetFocus(m_nZoomIndex);
    m_pSerialViscaManager->SetDZoom(m_nZoomIndex);

    SetLogMsg(BUTTON_CLICKED, "ZOOM_INDEX, " + ui->zoomRangePushButton->text());
    ConfigManager con = ConfigManager("parameter_enforcement.json");
    QJsonObject object = con.GetConfig();
    object["zoom index"] = (int)m_nZoomIndex + 1;
    con.SetConfig(object);
    con.SaveFile();

    SetLaserDetectionAreaDistance(m_nZoomIndex + 1);
}

void EnforcementComponentWidget::zoomRangeWithoutIncrement()
{
    if(m_nEnforcementMode == V)
        return;
     disconnect(m_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(doVModeZFControl(float, int)) );
//    int zoom_index = 0;
    if (m_UserModeOn)
    {
        if (m_nZoomIndex >= m_stmetervector.size())
            m_nZoomIndex = 0;

//        zoom_index = m_nZoomIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_stmetervector[m_nZoomIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_stfeetvector[m_nZoomIndex]+distanceValue());
        }
    }
    else
    {
        if (m_nZoomIndex >= m_ltmetervector.size())
            m_nZoomIndex = 0;

//        zoom_index = m_nZoomIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_ltmetervector[m_nZoomIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_ltfeetvector[m_nZoomIndex]+distanceValue());
        }
    }

    qDebug() << "zoom_index" << m_nZoomIndex;
    m_pSerialViscaManager->SetZoom(m_nZoomIndex);
    m_pSerialViscaManager->SetFocus(m_nZoomIndex);
    m_pSerialViscaManager->SetDZoom(m_nZoomIndex);

    SetLogMsg(BUTTON_CLICKED, "ZOOM_INDEX, " + ui->zoomRangePushButton->text());
    ConfigManager con = ConfigManager("parameter_enforcement.json");
    QJsonObject object = con.GetConfig();
    object["zoom index"] = (int)m_nZoomIndex + 1;
    con.SetConfig(object);
    con.SaveFile();

    SetLaserDetectionAreaDistance(m_nZoomIndex + 1);
}
//void EnforcementComponentWidget::unitInit()
//{

//}

void EnforcementComponentWidget::initRec()
{
    ui->recLabel->setColor(Qt::red);
    ui->recLabel->setText(LoadString("IDS_REC"));
    ui->recLabel->setAlignment(Qt::AlignLeft);
    ui->recIconLabel->setImage("enforcement", "redcircle.png");
    ui->recIconLabel->setAlignment(Qt::AlignRight);
//    ui->recIconLabel->resize(ui->rec)
}

void EnforcementComponentWidget::setVehicleMode()
{
    if (!m_bTruckChecked && !m_bBikeChecked)
    {
        m_nVehicleMode = Normal;
        SetLogMsg(BUTTON_CLICKED, "CAPTURE CAR," + QString::number(m_captureSpeed[0].toDouble(), 'f' , 1));
    }
    else if (m_bTruckChecked && !m_bBikeChecked)
    {
        m_nVehicleMode = Truck;
        SetLogMsg(BUTTON_CLICKED, "CAPTURE TRUCK," + QString::number(m_captureSpeed[1].toDouble(), 'f' , 1));
    }
    else if (!m_bTruckChecked && m_bBikeChecked)
    {
        m_nVehicleMode = MotoCycle;
        SetLogMsg(BUTTON_CLICKED, "CAPTURE TRUCK," + QString::number(m_captureSpeed[2].toDouble(), 'f' , 1));
    }
    DisplaySpeedLimit();
    return;
    //        assert();
}

QString EnforcementComponentWidget::GetMode()
{
    QString mode;
    if (m_UserModeOn)
        mode.append("U");
    else
        mode.append("N");

    ConfigManager config = ConfigManager("parameter_setting1.json");
    QJsonObject object = config.GetConfig();
    switch(object["enforcement selection"].toInt())
    {
    case 1:
    {
        mode.append("I");
    }
        break;
    case 2:
    {
        mode.append("A");
    }
        break;
    case 3:
    {
        mode.append("V");
    }
        break;
    }

    switch(m_nVehicleMode)
    {
    case Normal:
    {
        mode.append("N");
    }
        break;
    case Truck:
    {
        mode.append("T");
    }
        break;
    case MotoCycle:
    {
        mode.append("M");
    }
        break;
    }

    if (m_UserModeOn)
    {
        mode.append(QString("%1").arg(QString::number(m_nZoomIndex + 1), 2));
    }
    else
    {
        mode.append(QString("%1").arg(QString::number(m_nZoomIndex + 1), 2));
    }

    return mode;
}

void EnforcementComponentWidget::doVModeTimer(bool bVModeTimerWorking)
{
    if (bVModeTimerWorking && m_nMode != Ready)
    {
        if (!m_bVModeTimerWorking)
        {
            VModeVideoSave();
            m_VModeTimer.start(m_nVModeSecond * 1000);
            m_bVModeTimerWorking = true;
            doEnforceMode(true);
        }
    }
    else
    {
        if (m_bVModeTimerWorking)
        {
            m_VModeTimer.stop();
            m_bVModeTimerWorking = false;
            doEnforceMode(false);
        }
    }
    return;
}

void EnforcementComponentWidget::doEnforceMode(bool bEnforced)
{
    if (bEnforced)
    {
        displayRedOutline(true);
        ui->recLabel->show();
        ui->recIconLabel->show();

    }
    else
    {
        displayRedOutline(false);
        ui->recLabel->hide();
        ui->recIconLabel->hide();

    }
}

void EnforcementComponentWidget::doPreManualMode()
{
    hudClear();

    QFile File(TRIGGER_FILE);
    QByteArray ba;
    if(File.open(QFile::ReadOnly | QFile::Text))
    {
          ba = File.readAll();
    }
    else
    {
          qDebug()<<"ERROR:"<<File.errorString();
    }

    char value = ba[0];
    if (value == '0')
    {
        m_triggerStatus = PRESS;
        doATMode();
    }
    else if (value == '1')
    {
        m_triggerStatus = RELEASE;
        doReadyMode();
    }
    else
    {
        m_triggerStatus = SKIP;
    }

    File.close();

}

void EnforcementComponentWidget::clearSpeed()
{
    m_hudManager.HUDEnforcementSpeedClear();

    ui->speedLabel->clear();
    if(m_nEnforcementMode == V)
        doEnforceMode(true);
    else
        doEnforceMode(false); //REC label clear(false)
}

void EnforcementComponentWidget::clearDistance()
{
    m_pDistanceLabel->setColor(Qt::white);
    m_pDistanceLabel->setText("----.-" + distanceValue());

    m_hudManager.HUDEnforcementDistanceClear();


}

void EnforcementComponentWidget::setPSerialViscaManager(SerialViscaManager *newPSerialViscaManager)
{
    m_pSerialViscaManager = newPSerialViscaManager;
}


void EnforcementComponentWidget::setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager)
{
    if (m_pSerialLaserManager == nullptr)
        m_pSerialLaserManager = newPSerialLaserManager;
}

void EnforcementComponentWidget::paintEvent(QPaintEvent *event)
{
//    QWidget::paintEvent(event);

        QPainter painter(this);
    //    QStyleOptionFrame  option;

    //    option.initFrom(this);
    //    option.rect = ui->verticalLayout_2->geometry();
    //    option.lineWidth = 1;
    //    option.frameShape = QFrame::Box;
    //    style()->drawPrimitive(QStyle::PE_Frame,  &option,  &painter,  this);

    //    QStyleOptionFrame  option2;
    //    option2.initFrom(this);
    //    option2.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_7->geometry().top() + ui->gridLayout_2->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    //    option2.lineWidth = 1;
    //    option2.frameShape = QFrame::HLine;
    //    style()->drawPrimitive(QStyle::PE_Frame,  &option2,  &painter,  this);

    //    QStyleOptionFrame  option3;
    //    option3.initFrom(this);
    //    option3.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_5->geometry().top() + ui->horizontalLayout_7->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    //    option3.lineWidth = 1;
    //    option3.frameShape = QFrame::HLine;
    //    style()->drawPrimitive(QStyle::PE_Frame,  &option3,  &painter,  this);

        if (m_bRedLine)
        {
            int gap = 0;

            QPen Pen(Qt::red);
            Pen.setStyle(Qt::SolidLine);
            Pen.setWidth(10);

            painter.setPen(Pen);
    //        painter.drawRect(GetWidgetSizePos(QRect(0, 0, 1600, 960)));
//            painter.drawLine(gap, gap, width() - 2 * gap, gap);
            painter.drawLine(gap, gap, gap, height());
            painter.drawLine(width() - gap, gap, width(), height());
            painter.drawLine(gap, height(), width(), height());


        }
        QPen crossPen;
        if (m_bRedLine)
        {
            crossPen.setColor(Qt::red);
        }
        else
        {
            crossPen.setColor(Qt::white);
        }

        crossPen.setStyle(Qt::SolidLine);
        crossPen.setWidthF(0);
        int height2 = height() - m_MainMenuWidgetSize.height();;
        int gap = 1;
        int reticle_width = 5;
        int x = m_cross.x() * 800 / 1920;
        int y = m_cross.y() * 480 / 1080;

        QRect rect = QRect(QPoint(((width() / 2 ) + x) - reticle_width * gap, ((height2 / 2) + y) - gap), QPoint(((width() / 2) + x) + reticle_width*gap, ((height2 / 2) + y) + gap));
        QRect rect2 = QRect(QPoint(((width() / 2) + x) - gap, ((height2 / 2) + y) - reticle_width * gap), QPoint(((width() / 2) + x) + gap, ((height2 / 2) + y) + reticle_width * gap));

        if (m_bRedLine)
        {
            painter.fillRect(rect, Qt::red);
            painter.fillRect(rect2, Qt::red);
        }
        else
        {
            painter.fillRect(rect, Qt::white);
            painter.fillRect(rect2, Qt::white);
        }

}

void EnforcementComponentWidget::on_zoomRangePushButton_clicked()
{
    zoomRange();

}

void EnforcementComponentWidget::on_readyPushButton_clicked()
{
    switch (m_nMode)
    {
    case Ready:
    {
        ui->readyPushButton->setText(LoadString("IDS_AT"));
        m_nMode = AT;
        disconnect(&m_fileSystemWatcher,SIGNAL(fileChanged(QString)),this,SLOT(do_FileSystemWatcher(QString)));
        doATMode();

    }
        break;
    case AT:
    {

        ui->readyPushButton->setText(LoadString("IDS_Manual"));
        m_nMode = Manual;
        doPreManualMode();
        m_fileSystemWatcher.addPath(TRIGGER_FILE);
        //동작 안해서 임시로
//        connect(&m_fileSystemWatcher,SIGNAL(fileChanged(QString)),this,SLOT(do_FileSystemWatcher(QString)));
        m_ManualTimer.start(500);
        SetLogMsg(BUTTON_CLICKED, "MANUAL_MODE");
//        doManualMode();
    }
        break;
    case Manual:
    {
//        m_ManualModeTimer.stop();
        ui->readyPushButton->setText(LoadString("IDS_Ready"));
        m_nMode = Ready;
//        disconnect(&m_fileSystemWatcher,SIGNAL(fileChanged(QString)),this,SLOT(do_FileSystemWatcher(QString)));
        m_ManualTimer.stop();
        doReadyMode();
    }
        break;
    }
}


void EnforcementComponentWidget::on_dzPlusPushButton_clicked()
{
    dzPlus();
}


void EnforcementComponentWidget::on_dzMinusPushButton_clicked()
{
    dzMinus();
}

void EnforcementComponentWidget::on_showCaptureSpeedDistance(float fSpeed, float fDistance, int VehicleId)
{
    //NightMode?
//    if (m_bNight)
//    {
//        m_pSerialLaserManager->stop_laser();
//        m_pSerialLaserManager->start_laser();
//        m_pSerialLaserManager->request_distance(true);
//        m_bNight = false;
//        return;
//    }

    m_fSpeed = fSpeed;
    m_fDistance = fDistance;

    if (m_nEnforcementMode == V)
    {
        return; //v mode 일 시 단속 x
    }

    if (getSpeedValue(fSpeed) >= GetCaptureSpeedLimit())
    {
        if (VehicleLastId != VehicleId)
        {
            SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();

//            disconnect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), this, SLOT(on_showCaptureSpeedDistance(float,float, int)));
            disconnect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), this, SLOT(on_showSpeedDistance(float,float)));
            disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float, int)));

            m_WhiteDistanceClearTimer.stop();
            m_WhiteSpeedClearTimer.stop();

            VehicleLastId = VehicleId;
            // 화면에 속도 및 거리, REC 표시 출력
            displaySpeedDistance(fSpeed, fDistance, Qt::red, true);

            // HUD에 속도 및 거리, REC 표시 출력
//            displayHudSpeedDistance(true, true, true, true);
        //    빨간색 테두리 표시 등
            doEnforceMode(true);
//

        //        이미지 또는 동영상을 설정대로 저장
            SaveImageVideo();
            //썸네일 표시 처리, 썸네일 위에 단속 정보 표시 처리 출력
            displayThumbnailSpeedDistance(fSpeed, fDistance);

            m_hudManager.HUDEnforcementLimitOver(fSpeed, fDistance);

//            disconnect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), &m_hudManager.hud(), SLOT(showCaptureSpeedDistance(float, float, int)));
//            disconnect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), &m_hudManager.hud(), SLOT(showSpeedDistanceSensitivity(float, float)));
//            disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), &m_hudManager.hud(), SLOT(showDistanceSensitivity(float, int)));
            QTimer::singleShot(500, this, SLOT(RestartSignal()));

            snapshotSound->play();
//            m_RedTimer.start(500);

//            sleep(1);

        }
    }
    else if (getSpeedValue(fSpeed) < GetCaptureSpeedLimit())
    {
//        화면에 속도 및 거리 출력
        displaySpeedDistance(fSpeed, fDistance, Qt::white, false);

//        HUD에 속도 및 거리 출력
        m_hudManager.HUDEnforcement(false, fSpeed, fDistance);

        if(m_nEnforcementMode == V)
            doEnforceMode(true);
        else
            doEnforceMode(false);
        //        m_WhiteClearTimer.start(200);
        m_WhiteSpeedClearTimer.start(200);
        m_WhiteDistanceClearTimer.start(200);
//        로그 저장
    }

    //NightMode
    if(m_bNight==true)
    {
        m_pSerialLaserManager->start_laser();
//        m_pSerialLaserManager->request_distance(true);
//        if (m_bVirtualMode)
//            m_pSerialLaserManager->start_virtualSpeed();
    }
}

void EnforcementComponentWidget::on_showSpeedDistance(float fSpeed, float fDistance)
{
    m_fSpeed = fSpeed;
    m_fDistance = fDistance;

//    화면에 속도 및 거리 출력
    displaySpeedDistance(fSpeed, fDistance, Qt::white, false);
//        HUD에 속도 및 거리 출력
    m_hudManager.HUDEnforcement(false, fSpeed, fDistance);

    if(m_nEnforcementMode == V)
        doEnforceMode(true);
    else
        doEnforceMode(false);
//        로그 저장
//    m_WhiteClearTimer.start(200);
    m_WhiteSpeedClearTimer.start(200);
    m_WhiteDistanceClearTimer.start(200);
}

void EnforcementComponentWidget::on_showDistance(float fDistance, int nSensitivity)
{
    m_fDistance = fDistance;

//    화면에 거리 출력
    displayDistance(fDistance);
//	HUD에 거리 출력
//    m_hudManager.HUDEnforcement(false, 0, fDistance);
    m_hudManager.HUDEnforcementDistance(false, 0, fDistance);

    //    displayRedOutline(false);
//    로그 저장
//    m_WhiteClearTimer.start(200);
    m_WhiteDistanceClearTimer.start(200);
}

void EnforcementComponentWidget::on_Night()
{
    m_bNight = true;

}

void EnforcementComponentWidget::on_STMode()
{
    m_UserModeOn = true;
    zoomRangeWithoutIncrement();
}

void EnforcementComponentWidget::on_LTMode()
{
    m_UserModeOn = false;
    zoomRangeWithoutIncrement();
}

void EnforcementComponentWidget::on_EnforceModeI()
{
    if (m_nEnforcementMode != I)
        g_nCrackDownIndex = 1;
    m_nEnforcementMode = I;
    doVModeTimer(false);
    zoomRangeWithoutIncrement();

    //setting night mode
    ConfigManager config = ConfigManager("parameter_setting2.json");
    QJsonObject object = config.GetConfig();
    int dn = object["day&night selection"].toInt();
    if (dn >= 0 && dn <=3)
    {
        m_pSerialLaserManager->set_night_mode(0);
        m_bNight = false;
    }
    else
    {
        m_pSerialLaserManager->set_night_mode(1);
        m_bNight = true;
    }
}

void EnforcementComponentWidget::on_EnforceModeA()
{
    if (m_nEnforcementMode != A)
        g_nCrackDownIndex = 1;
    m_nEnforcementMode = A;
    doVModeTimer(false);
    zoomRangeWithoutIncrement();

    //setting night mode
    ConfigManager config = ConfigManager("parameter_setting2.json");
    QJsonObject object = config.GetConfig();
    int dn = object["day&night selection"].toInt();
    if (dn >= 0 && dn <=3)
    {
        m_pSerialLaserManager->set_night_mode(0);
        m_bNight = false;
    }
    else
    {
        m_pSerialLaserManager->set_night_mode(1);
        m_bNight = true;
    }
}

void EnforcementComponentWidget::on_EnforceModeV()
{
    if (m_nEnforcementMode != V)
        g_nCrackDownIndex = 1;
    m_nEnforcementMode = V;

    //change zoombutton, disable indicator
    ui->zoomRangePushButton->setText("Z: AUTO");
    doVMode();
    m_pSerialLaserManager->set_night_mode(0); //V mode not require nightMode
    m_bNight = false;
}

void EnforcementComponentWidget::do_FileSystemWatcher(const QString &path)
{
    QFile File(path);
    QByteArray ba;
    if(File.open(QFile::ReadOnly | QFile::Text))
    {
          ba = File.readAll();
    }
    else
    {
          qDebug()<<"ERROR:"<<File.errorString();
    }

    char value = ba[0];
    if (value == '0' && m_triggerStatus != PRESS)
    {
        m_triggerStatus = PRESS;
        doATMode();
    }
    else if (value == '1' && m_triggerStatus != RELEASE)
    {
        m_triggerStatus = RELEASE;
        doReadyMode();
    }
    else
    {
        m_triggerStatus = SKIP;
    }

    if (File.exists())
        m_fileSystemWatcher.addPath(path);

    File.close();
}

void EnforcementComponentWidget::do_FileSystemWatcherTimer()
{
    QFile File(TRIGGER_FILE);
    QByteArray ba;
    if(File.open(QFile::ReadOnly | QFile::Text))
    {
          ba = File.readAll();
    }
    else
    {
          qDebug()<<"ERROR:"<<File.errorString();
    }
    File.close();

    char value = ba[0];
    if (value == '0' && m_triggerStatus != PRESS)
    {
        m_triggerStatus = PRESS;
        doATMode();
    }
    else if (value == '1' && m_triggerStatus != RELEASE)
    {
        m_triggerStatus = RELEASE;
        doReadyMode();
    }
    else
    {
        m_triggerStatus = SKIP;
    }
}

void EnforcementComponentWidget::timerEvent(QTimerEvent *event)
{
//    m_bTest = !m_bTest;
//    if (m_bTest)
//    {
//        displaySpeedDistance(0, 0, Qt::red, true);
//        doEnforceMode(true);
//    }
//    else
//    {
//        QTimer::singleShot(500, this, SLOT(RestartSignal()));
//    }
    StorageManager storageManager;
    if (storageManager.GetSDExitEnforcement())
    {
        float sdpercent = storageManager.GetSDAvailable() / storageManager.GetSDTotal() * 100;
        QString sdCardValue = LoadString("IDS_SD_CARD") + QString::number(sdpercent, 'f', 1) + "%";
        BaseDialog baseDialog(SdCardMemoryLackType, Qt::AlignmentFlag::AlignCenter, sdCardValue, false, LoadString("IDS_WARNING_MESSAGE"));
        if (baseDialog.exec() == QDialog::Accepted)
        {
            emit sig_exit();
        }
    }
}


//void EnforcementComponentWidget::on_truckPushButton_toggled(bool checked)
//{
//    if (ui->bikePushButton->isDown())
//    {
//        ui->bikePushButton->setDown(false);
//        //        m_bBikeChecked = !m_bBikeChecked;
//    }
//    ui->truckPushButton->setChecked()
//    ui->truckPushButton->setDown(checked);
//    //if (ui->truckPushButton->isDown())
////{
//////        m_bTruckChecked = !m_bTruckChecked;
////    ui->truckPushButton->setDown(false);
////}
////else
////{
////    ui->truckPushButton->setDown(true);
////}
////    if (ui->bikePushButton->isChecked())
////    {
////        ui->bikePushButton->setDown(false);
//////        m_bTruckChecked = false;
////    }

////    ui->truckPushButton->setDown(checked);
////    m_bTruckChecked = true;

//}


//void EnforcementComponentWidget::on_bikePushButton_toggled(bool checked)
//{
//    if (ui->truckPushButton->isDown())
//    {
//        ui->truckPushButton->setDown(false);
////        m_bTruckChecked = !m_bTruckChecked;
//    }
//    ui->bikePushButton->setDown(checked);
////    if (ui->bikePushButton->isDown())
////    {
////        ui->bikePushButton->setDown(false);
////    }
////    else
////    {
////        ui->bikePushButton->setDown(true);
////    }
////    if (ui->truckPushButton->isChecked())
////    {
////        ui->truckPushButton->setDown(false);
////    }
////    ui->bikePushButton->setDown(checked);
////    m_bBikeChecked = true;

//}


void EnforcementComponentWidget::on_truckPushButton_clicked()
{
//    if (ui->bikePushButton->isDown())
//    {
//        ui->bikePushButton->setDown(false);
////        m_bBikeChecked = !m_bBikeChecked;
//    }
//    if (ui->truckPushButton->isDown())
//    {
////        m_bTruckChecked = !m_bTruckChecked;
//        ui->truckPushButton->setDown(false);
//    }
//    else
//    {
//        ui->truckPushButton->setDown(true);
//    }
    if (m_bBikeChecked)
    {
//        ui->bikePushButton->setDown(false);
        ui->bikePushButton->setStyleSheet("border-color: blue;");
        m_bBikeChecked = !m_bBikeChecked;
    }
    if (m_bTruckChecked)
    {
        m_bTruckChecked = !m_bTruckChecked;
        ui->truckPushButton->setStyleSheet("border-color: blue;");
    }
    else
    {
        m_bTruckChecked = !m_bTruckChecked;
//        ui->truckPushButton->setDown(true);
        ui->truckPushButton->setStyleSheet("border-color: red;");
    }
    setVehicleMode();
}


void EnforcementComponentWidget::on_bikePushButton_clicked()
{
    if (m_bTruckChecked)
    {
        ui->truckPushButton->setStyleSheet("border-color: blue;");
        m_bTruckChecked = !m_bTruckChecked;
    }
    if (m_bBikeChecked)
    {
        m_bBikeChecked = !m_bBikeChecked;
        ui->bikePushButton->setStyleSheet("border-color: blue;");
    }
    else
    {
        m_bBikeChecked = !m_bBikeChecked;
        ui->bikePushButton->setStyleSheet("border-color: red;");
    }
    setVehicleMode();
}


void EnforcementComponentWidget::on_saveImagePushButton_clicked()
{
    stEnforcementInfo enforceInfo;
    enforceInfo.nCaptureSpeed = (int)m_fSpeed;
    enforceInfo.nSpeedLimit = m_SpeedLimit[m_nVehicleMode].toInt();
    enforceInfo.nCaptureSpeedLimit = m_captureSpeed[m_nVehicleMode].toInt();
    enforceInfo.nDistance = (int)m_fDistance;
    enforceInfo.bUserMode = m_UserModeOn;
    enforceInfo.enforceMode = m_nEnforcementMode;
    enforceInfo.vehicle = m_nVehicleMode;
    enforceInfo.zoom_index = m_nZoomIndex;
    QDateTime datetime = QDateTime::currentDateTime();
    enforceInfo.date = datetime.toString("yyyyMMdd");
    enforceInfo.time = QString(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]);

    m_pCamera->SaveImage(MC, enforceInfo, MANUAL_CAPTURE);
//    QPixmap pixmap = m_pCamera->grab();
//    pixmap.save(GETSDPATH(MANUAL_CAPTURE) + "/" +GetFileName(MC, enforceInfo));
}

void EnforcementComponentWidget::StopHUDRec()
{
    if(m_nEnforcementMode == V)
        return;
    m_hudManager.ShowSpeed(true, false);
}

void EnforcementComponentWidget::ClearSpeedDisplay()
{
    clearSpeed();
}

void EnforcementComponentWidget::ClearDistanceDisplay()
{
    clearDistance();
}


void EnforcementComponentWidget::RestartSignal()
{
    SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
//    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), this, SLOT(on_showCaptureSpeedDistance(float,float, int)));
    connect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), this, SLOT(on_showSpeedDistance(float,float)));
    connect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float, int)));
//    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float, int)), &m_hudManager.hud(), SLOT(showCaptureSpeedDistance(float, float, int)));
//    connect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), &m_hudManager.hud(), SLOT(showSpeedDistanceSensitivity(float, float)));
//    connect(laser_packet, SIGNAL(sig_showDistance(float,int)), &m_hudManager.hud(), SLOT(showDistanceSensitivity(float, int)));
//    clearDistanceSpeed();
    clearSpeed();
    clearDistance();
}

void EnforcementComponentWidget::VModeVideoSave()
{
    stEnforcementInfo enforceInfo;
    enforceInfo.nCaptureSpeed = 0;
    enforceInfo.nSpeedLimit = m_SpeedLimit[m_nVehicleMode].toInt();
    enforceInfo.nCaptureSpeedLimit = m_captureSpeed[m_nVehicleMode].toInt();
    enforceInfo.nDistance = 0;
    enforceInfo.bUserMode = m_UserModeOn;
    enforceInfo.enforceMode = m_nEnforcementMode;
    enforceInfo.vehicle = m_nVehicleMode;
    enforceInfo.zoom_index = m_nZoomIndex + 1;
    QDateTime datetime = QDateTime::currentDateTime();
    enforceInfo.date = datetime.toString("yyyyMMdd");
    enforceInfo.time = QString(datetime.toString("hhmmss") + QString::number(datetime.time().msec())[0]);

    m_pCamera->SaveVideo(VV, enforceInfo, VIDEO);
}

void EnforcementComponentWidget::on_Show()
{
    show(true);
}

void EnforcementComponentWidget::on_Hide()
{
    hide(true);
}

//void EnforcementComponentWidget::on_ManualMode()
//{
//    if (m_triggerStatus == PRESS)
//        doATMode();
//    else if (m_triggerStatus == RELEASE)
//        doReadyMode();
//}

void EnforcementComponentWidget::SaveDZoomJson()
{
    ConfigManager config = ConfigManager("dzoom.json");
    QJsonObject object = config.GetConfig();

    QJsonArray ar;

    if(m_UserModeOn == 1)
        ar = object["st dzoom"].toArray();
    else
        ar = object["lt dzoom"].toArray();

    ar[m_nZoomIndex] = m_pSerialViscaManager->m_Dzoom_pqrs;

    if(m_UserModeOn == 1)
        object["st dzoom"] = ar;
    else
        object["lt dzoom"] = ar;

    config.SetConfig(object);
    config.SaveFile();
}

void EnforcementComponentWidget::doVMode()
{
    int distance = 1000, area = 1000;

    m_pSerialLaserManager->set_detection_distance(distance);
    m_pSerialLaserManager->set_detection_area(area);

    connect(m_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(doVModeZFControl(float, int)) );

}

void EnforcementComponentWidget::DisplaySpeedLimit()
{
    QString speedLimitCS;// = QString("CS: %1%2").arg(QString::number(m_captureSpeed[0].toInt())).arg(speedUnitValue());
    QString speedLimitT;// = QString("T: %1%2").arg(QString::number(m_captureSpeed[1].toInt())).arg(speedUnitValue());
    QString speedLimitM;// = QString("M: %1%2").arg(QString::number(m_captureSpeed[2].toInt())).arg(speedUnitValue());
    QString speedLimit;
    switch (m_nVehicleMode)
    {
    case Normal:
    {
        speedLimitCS = QString("CS: %1%2").arg(QString::number(m_captureSpeed[0].toInt())).arg(speedUnitValue());
        speedLimitT = QString(" T: %1%2").arg(QString::number(m_captureSpeed[1].toInt())).arg(speedUnitValue());
        speedLimitM = QString(" M: %1%2").arg(QString::number(m_captureSpeed[2].toInt())).arg(speedUnitValue());
        speedLimit = QString("<font color= \"%1\"><strong>%2</strong></font><br> <font color= \"%3\">%4</font><br><font color= \"%5\">%6</font>")
            .arg("black")
            .arg(speedLimitCS)
            .arg("gray")
            .arg(speedLimitT)
            .arg("gray")
            .arg(speedLimitM);
    }
        break;
    case Truck:
    {
        speedLimitCS = QString(" CS: %1%2").arg(QString::number(m_captureSpeed[0].toInt())).arg(speedUnitValue());
        speedLimitT = QString("T: %1%2").arg(QString::number(m_captureSpeed[1].toInt())).arg(speedUnitValue());
        speedLimitM = QString(" M: %1%2").arg(QString::number(m_captureSpeed[2].toInt())).arg(speedUnitValue());
        speedLimit = QString("<font color= \"%1\">%2</font><br> <font color= \"%3\"><strong>%4</strong></font><br><font color= \"%5\">%6</font>")
            .arg("gray")
            .arg(speedLimitCS)
            .arg("black")
            .arg(speedLimitT)
            .arg("gray")
            .arg(speedLimitM);
    }
        break;
    case MotoCycle:
    {
        speedLimitCS = QString(" CS: %1%2").arg(QString::number(m_captureSpeed[0].toInt())).arg(speedUnitValue());
        speedLimitT = QString(" T: %1%2").arg(QString::number(m_captureSpeed[1].toInt())).arg(speedUnitValue());
        speedLimitM = QString("M: %1%2").arg(QString::number(m_captureSpeed[2].toInt())).arg(speedUnitValue());
        speedLimit = QString("<font color= \"%1\">%2</font><br> <font color= \"%3\">%4</font><br><font color= \"%5\"><strong>%6</strong></font>")
            .arg("gray")
            .arg(speedLimitCS)
            .arg("gray")
            .arg(speedLimitT)
            .arg("black")
            .arg(speedLimitM);
    }
        break;
    }

    ui->speedLimitLabel->setText(speedLimit);
    ui->speedLimitLabel->setFontSize(21);
    ui->speedLimitLabel->setDisabled(true);
}

//void EnforcementComponentWidget::PushFile(QString file_name)
//{
//    m_mutex->lock();
//    m_FileQueue->enqueue(file_name);
//    m_mutex->unlock();
//}

void EnforcementComponentWidget::doVModeZFControl(float fDistance, int notuse)
{
    if(m_isZFWorking == true)
    {
        return;
    }
    m_isZFWorking = true;
    static float fDistanceAvg = fDistance;
    static int counter = 0;
    ++counter;

    fDistanceAvg = fDistanceAvg * (2.0/3.0) + fDistance * (1.0/3.0);

    if(counter<5)
    {
        m_isZFWorking = false;
        return;
    }
    else if(counter > 100000)
        counter = 6;

    if(fDistanceAvg >= 2000)
    {
        m_isZFWorking = false;
        return;
    }
    else if(fDistanceAvg < 10)
    {
        m_isZFWorking = false;
        return;
    }

    int nZoomIndex = 0;
    static int nFormalZoomIndex = 0;

    if(fDistanceAvg >= 10 && fDistanceAvg <36)
    {
        nZoomIndex = 0;
    }
    else if(fDistanceAvg >= 36 && fDistanceAvg <60)
    {
        nZoomIndex = 1;
    }
    else if(fDistanceAvg >= 60 && fDistanceAvg <100)
    {
        nZoomIndex = 2;
    }
    else if(fDistanceAvg >= 100 && fDistanceAvg <160)
    {
        nZoomIndex = 3;
    }
    else if(fDistanceAvg >= 160)
    {
        nZoomIndex = 4;
    }
    else
    {
        m_isZFWorking = false;
        return;
    }


    QJsonObject object = ConfigManager("parameter_setting2.json").GetConfig();
    int ndaynight = object["day&night selection"].toInt();

    if(nFormalZoomIndex == nZoomIndex)
    {

    }
    else
    {
        m_pSerialViscaManager->setZFcontrolThread(nZoomIndex, ndaynight);
//        m_pSerialViscaManager->SetZoomForVmode(nZoomIndex);
//        m_pSerialViscaManager->SetFocusForVmode(nZoomIndex, ndaynight);
    }

//    if(count % 10 == 1)
//    {
//        QJsonObject object = ConfigManager("parameter_setting2.json").GetConfig();
//        int ndaynight = object["day&night selection"].toInt();

//        m_pSerialViscaManager->SetZoomForZoomFocus(nZoomIndex);
//        m_pSerialViscaManager->SetFocusForZoomFocus(nZoomIndex, ndaynight);
//    }
    nFormalZoomIndex = nZoomIndex;
    m_isZFWorking = false;
}

void EnforcementComponentWidget::on_saveImage()
{
    displayThumbnail();
}

void EnforcementComponentWidget::closeThread()
{
    if (m_pFtpThread->isRunning())
    {
        m_pFtpThread->requestInterruption();
    }
    m_pFtpThread->quit();
    m_pFtpThread->wait();
    m_pFtpThread = nullptr;
}


void EnforcementComponentWidget::on_setNightMode(int dn)
{
    if(m_nEnforcementMode == V)
    {
        m_pSerialLaserManager->set_night_mode(0);
        m_bNight = false;
    }
    else
    {
        if (dn >= 0 && dn <=3)
        {
            m_pSerialLaserManager->set_night_mode(0);
            m_bNight = false;
        }
        else
        {
            m_pSerialLaserManager->set_night_mode(1);
            m_bNight = true;
        }
    }
}
