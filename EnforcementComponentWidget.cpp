#include "EnforcementComponentWidget.h"
#include "ui_EnforcementComponentWidget.h"

#include <QPainter>
#include <QTime>

#include "StringLoader.h"
#include "camera.h"
#include "WidgetSize.h"
#include "HUDManager.h"
#include "SerialLaserManager.h"
#include "SerialViscaManager.h"
#include "SerialPacket.h"
#include "SpeedUnitManager.h"
#include "WidgetSize.h"

extern int g_nCrackDownIndex;

EnforcementComponentWidget::EnforcementComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementComponentWidget)
{
    ui->setupUi(this);

//    SetCamera();

    m_object = m_config.GetConfig();
    m_object2 = m_config2.GetConfig();

    ui->hidePushButton->setText(LoadString("IDS_HIDE"));
    ui->readyPushButton->setText(LoadString("IDS_READY"));
//    ui->zoomRangePushButton->setText("Z: 100~160 m");
    ui->dzPlusPushButton->setText(LoadString("IDS_DZ_PLUS"));
    ui->dzMinusPushButton->setText(LoadString("IDS_DZ_MINUS"));

    ui->saveImagePushButton->setText(LoadString("IDS_SAVE_IMAGE"));
    ui->truckPushButton->setImage("enforcement", "truck.jpg");
    ui->truckPushButton->setCheckable(true);
    ui->bikePushButton->setImage("enforcement", "bike.jpg");
    ui->bikePushButton->setCheckable(true);

    m_pReadyButton = ui->readyPushButton;

    m_captureSpeed = m_object["capture speed"].toArray();

    ui->speedLimitLabel->setText(QString("CS: %0%4\nT: %2%4\nM: %3%4").arg(QString::number(m_captureSpeed[0].toInt())).arg(QString::number(m_captureSpeed[1].toInt())).arg(QString::number(m_captureSpeed[2].toInt())).arg(speedUnit()));
    ui->speedLimitLabel->setDisabled(true);


    if (m_object["speed selection"].toInt() == 1)
        m_UserModeOn = true;
    else
        m_UserModeOn = false;

    ConfigManager con = ConfigManager("parameter_setting3.json");
    QJsonObject object = con.GetConfig();
    if (object["unit selection"].toInt() == 1)
        m_nDistance = meter;
    else
        m_nDistance = feet;

    QSizePolicy sp_retain = ui->hidePushButton->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->hidePushButton->setSizePolicy(sp_retain);
    ui->readyPushButton->setSizePolicy(sp_retain);
    ui->zoomRangePushButton->setSizePolicy(sp_retain);
    ui->dzPlusPushButton->setSizePolicy(sp_retain);
    ui->dzMinusPushButton->setSizePolicy(sp_retain);

    ui->saveImagePushButton->setSizePolicy(sp_retain);
    ui->truckPushButton->setSizePolicy(sp_retain);
    ui->bikePushButton->setSizePolicy(sp_retain);

    ui->speedLimitLabel->setSizePolicy(sp_retain);

    ui->enforcementCountLabel->setSizePolicy(sp_retain);
    ui->enforcementDistanceSpeedLabel->setSizePolicy(sp_retain);
    ui->enforcementTimeLabel->setSizePolicy(sp_retain);

    camInit();
    hudInit();
//    laserInit();
    initRec();

    ConfigManager config = ConfigManager("zoom_level.json");
    object = config.GetConfig();


    m_captureSpeed = object["st mode meter dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_stmetervector.push_back(item.toString());
    }
    m_captureSpeed = object["st mode feet dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_stfeetvector.push_back(item.toString());
    }
    m_captureSpeed = object["lt mode meter dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_ltmetervector.push_back(item.toString());
    }
    m_captureSpeed = object["lt mode feet dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_ltfeetvector.push_back(item.toString());
    }
    if (m_UserModeOn)
    {
        if (m_nDistance == meter)
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_stmetervector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
        else
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_stfeetvector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
    }
    else
    {
        if (m_nDistance == meter)
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_ltmetervector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
        else
            ui->zoomRangePushButton->setText(QString("%1%2").arg(m_ltfeetvector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
    }

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
    if (m_pCamera)
    {
        delete m_pCamera;
        m_pCamera = nullptr;
    }
    delete ui;
}

void EnforcementComponentWidget::dzPlus()
{
    SerialViscaManager serialViscaManager;
    serialViscaManager.plus_dzoom();
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
    SerialViscaManager serialViscaManager;
    serialViscaManager.minus_dzoom();//    if (m_UserModeOn)
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

void EnforcementComponentWidget::SaveImage()
{

}

void EnforcementComponentWidget::on_hidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->hidePushButton->setText(LoadString("IDS_HIDE"));
        hide();
    }
    else
    {
        ui->hidePushButton->setText(LoadString("IDS_SHOW"));
        show();
    }
}

void EnforcementComponentWidget::doShartAction()
{

}

void EnforcementComponentWidget::hide()
{
    m_isSetOutLine = true;
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
}

void EnforcementComponentWidget::show()
{
    m_isSetOutLine = false;
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
}

void EnforcementComponentWidget::SetCamera()
{
     m_pCamera = new Camera(this);
     m_pCamera->setGeometry(GetWidgetSizePos(QRect(0, 0, 1600, 960)));

     qDebug() << m_pCamera->geometry();
     m_pCamera->lower();
     m_pCamera->show();
}

void EnforcementComponentWidget::camInit()
{
    SerialViscaManager serialViscaManager;
    serialViscaManager.SetDayMode(m_object2["day&night selection"].toInt());

    serialViscaManager.set_IRCorrection_standard();

    serialViscaManager.set_manual_focus();
    serialViscaManager.separate_zoom_mode();
    serialViscaManager.dzoom(1);

//    ConfigManager config = ConfigManager("parameter_enforcement.json");
//    QJsonObject object = config.GetConfig();

}

void EnforcementComponentWidget::hudInit()
{
    HUDManager hudManager;

    ConfigManager config = ConfigManager("parameter_setting2.json");
    QJsonObject object = config.GetConfig();
    switch (object["reticle selection"].toInt())
    {
    case 1:
    {
        hudManager.SetReticleShape(Dot);
    }
        break;
    case 2:
    {
        hudManager.SetReticleShape(Cross);
    }
        break;
    case 3:
    {
        hudManager.SetReticleShape(Round);
    }
        break;
    case 4:
    {
        hudManager.SetReticleShape(Rectangle);
    }
        break;
    }

    ConfigManager config2 = ConfigManager("parameter_reticle.json");
    QJsonObject object2 = config2.GetConfig();
    QJsonArray array = object2["HUD reticle pos"].toArray();

    //hudManager.SetReticleShape()
}

void EnforcementComponentWidget::laserInit()
{
//     if (m_pSerialLaserManager == nullptr)
//        m_pSerialLaserManager = new SerialLaserManager;
    ConfigManager config = ConfigManager("parameter_settings1.json");
    QJsonObject object = config.GetConfig();
    ConfigManager config2 = ConfigManager("parameter_settings2.json");
    QJsonObject object2 = config2.GetConfig();

    m_pSerialLaserManager->set_weather_mode(object2["weather selection"].toInt());
    m_pSerialLaserManager->set_AJamming_mode(object2["anti-jamming selection"].toInt());
    m_pSerialLaserManager->set_buzzer_mode(object2["buzzer selection"].toInt());

    m_pSerialLaserManager->set_detection_distance(object["speed_selection"].toInt());

    ConfigManager config3 = ConfigManager("parameter_enforcement.json");
    QJsonObject object3 = config3.GetConfig();

    int zoom_index = object3["zoom index"].toInt();

    SetLaserDetectionAreaDistance(zoom_index);

    int dn = object["day&night selection"].toInt();
    if (dn >= 0 && dn <=3)
        m_pSerialLaserManager->set_night_mode(0);
    else
        m_pSerialLaserManager->set_night_mode(1);
    m_pSerialLaserManager->set_speed_measure_mode(1);
}

void EnforcementComponentWidget::doATMode()
{
    m_pSerialLaserManager->stop_laser();
    m_pSerialLaserManager->request_distance(false);

    SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
    m_pSerialLaserManager->start_laser();
    m_pSerialLaserManager->request_distance(true);
    if (m_bVirtualMode)
        m_pSerialLaserManager->start_virtualSpeed();
    connect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float)), this, SLOT(on_showCaptureSpeedDistance(float,float)));
    connect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), this, SLOT(on_showSpeedDistance(float,float)));
    connect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float, int)));
}

void EnforcementComponentWidget::doManualMode()
{
    doATMode();
}

void EnforcementComponentWidget::doReadyMode()
{
    SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();

    m_pSerialLaserManager->stop_laser();
    m_pSerialLaserManager->request_distance(false);

    displayRedOutline(false);

    disconnect(laser_packet, SIGNAL(sig_showCaptureSpeedDistance(float,float)), this, SLOT(on_showCaptureSpeedDistance(float,float)));
    disconnect(laser_packet, SIGNAL(sig_showSpeedDistance(float,float)), this, SLOT(on_showSpeedDistance(float,float)));
    disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float, int)));

}

int EnforcementComponentWidget::GetCaptureSpeedLimit()
{
    switch (m_nVehicleMode)
    {
    case Normal:
    {
        return getSpeedValue(m_captureSpeed.at(0).toInt());
    }
        break;
    case Truck:
    {
        return getSpeedValue(m_captureSpeed.at(1).toInt());
    }
        break;
    case MotoCycle:
    {
        return getSpeedValue(m_captureSpeed.at(2).toInt());
    }
        break;
    }
}

void EnforcementComponentWidget::initStyle()
{

}

void EnforcementComponentWidget::displaySpeedDistance(float fSpeed, float fDistance, QColor color, bool nRec)
{
    ui->distanceLabel->setColor(color);
    ui->distanceLabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distance());
    // REC
    ui->speedLabel->setColor(color);
    ui->speedLabel->setText(QString::number(getSpeedValue(fSpeed))+speedUnit());
    if (nRec)
    {
        ui->recLabel->show();
        ui->recIconLabel->show();
    }
    else
    {
        ui->recLabel->hide();
        ui->recIconLabel->hide();
    }
}

void EnforcementComponentWidget::displayDistance(float fDistance)
{
    ui->distanceLabel->setColor(Qt::white);
    ui->distanceLabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distance());
}

void EnforcementComponentWidget::displayRedOutline(bool nOn)
{
    if (nOn)
    {
        m_isSetOutLine = true;
    }
    else
    {
        m_isSetOutLine = false;
    }
}

void EnforcementComponentWidget::ImageVideoSave()
{
    QJsonObject object = m_config.GetConfig();
    switch(object["enforcement selection"].toInt())
    {
    case 1:
    {

    }
        break;
    case 2:
    {

    }
        break;
    case 3:
    {

    }
        break;
    }
}

void EnforcementComponentWidget::displayThumbnail(float fSpeed, float fDistance)
{
    ui->enforcementCountLabel->setText(QString::number(++g_nCrackDownIndex));
    ui->enforcementTimeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    ui->enforcementDistanceSpeedLabel->setText(QString::number(getSpeedValue(fSpeed)) + distance() + ", " + QString::number(getDistanceValue(fDistance)) + speedUnit());

//    QPixmap pixmap;
//    pixmap.grabWidget(m_pCamera);
    ui->thumbnailLabel->setPixmap(m_pCamera->grab());
}

void EnforcementComponentWidget::displayHudSpeedDistance(bool nDisplay, bool nSpeed, bool nRec, bool nUnit)
{
    HUDManager hudManager;
    hudManager.ShowSpeed(nSpeed, nRec);
    hudManager.ShowDistance(nDisplay);
    hudManager.ShowDistanceUnit(nUnit);
}

void EnforcementComponentWidget::displayHudDistance(bool nDisplay, bool nUnit)
{
    HUDManager hudManager;
    hudManager.ShowDistance(nDisplay);
    hudManager.ShowDistanceUnit(nUnit);
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
    }

    m_pSerialLaserManager->set_detection_distance(distance);
    m_pSerialLaserManager->set_detection_area(area);
}

void EnforcementComponentWidget::zoomRange()
{
    int zoom_index = 0;
    if (m_UserModeOn)
    {
        m_nStIndex++;
        if (m_nStIndex == m_stmetervector.size())
            m_nStIndex = 0;

        zoom_index = m_nStIndex;
        if (distanceValue() == meter)
        {
            ui->zoomRangePushButton->setText(m_stmetervector[m_nStIndex]+distance());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_stfeetvector[m_nStIndex]+distance());
        }
    }
    else
    {
        m_nLtIndex++;
        if (m_nLtIndex == m_ltmetervector.size())
            m_nLtIndex = 0;

        zoom_index = m_nLtIndex;
        if (distanceValue() == meter)
        {
            ui->zoomRangePushButton->setText(m_ltmetervector[m_nLtIndex]+distance());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_ltfeetvector[m_nLtIndex]+distance());
        }

    }

    SetLaserDetectionAreaDistance(zoom_index);
}

//void EnforcementComponentWidget::unitInit()
//{

//}

void EnforcementComponentWidget::initRec()
{
    ui->recLabel->setColor(Qt::red);
    ui->recLabel->setText("IDS_REC");
    ui->recIconLabel->setImage("enforcement", "redcircle.png");
    ui->recLabel->hide();
    ui->recIconLabel->hide();
}

void EnforcementComponentWidget::setVehicleMode()
{
    if (m_bTruckChecked && m_bBikeChecked)
        m_nVehicleMode = Normal;
    else if (m_bTruckChecked && !m_bBikeChecked)
        m_nVehicleMode = Truck;
    else if (!m_bTruckChecked && m_bBikeChecked)
        m_nVehicleMode = MotoCycle;
    return;
//        assert();
}


void EnforcementComponentWidget::setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager)
{
    if (m_pSerialLaserManager == nullptr)
        m_pSerialLaserManager = newPSerialLaserManager;
}

void EnforcementComponentWidget::paintEvent(QPaintEvent *event)
{
//    QWidget::paintEvent(event);

    if (m_isSetOutLine)
    {
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

        int gap = 3;

        QPen Pen(Qt::red);
        Pen.setStyle(Qt::SolidLine);
        Pen.setWidth(10);
        painter.setPen(Pen);
        painter.drawLine(gap, gap, getScreenWidth() - 2 * gap, gap);
        painter.drawLine(gap, gap, gap, getScreenHeight());
        painter.drawLine(getScreenWidth() - gap, gap, getScreenWidth() - 2 * gap, getScreenHeight() - 2 * gap);
        painter.drawLine(gap, getScreenHeight() - 2 * gap, getScreenWidth() - 2 * gap, getScreenHeight() - 2 * gap);
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
        doATMode();
    }
        break;
    case AT:
    {
        ui->readyPushButton->setText(LoadString("IDS_Manual"));
        m_nMode = Manual;
        doManualMode();
    }
        break;
    case Manual:
    {
        ui->readyPushButton->setText(LoadString("IDS_Ready"));
        m_nMode = Ready;
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

void EnforcementComponentWidget::on_showCaptureSpeedDistance(float fSpeed, float fDistance)
{
    if (m_bNight)
    {
        m_pSerialLaserManager->stop_laser();
        m_pSerialLaserManager->start_laser();
        m_pSerialLaserManager->request_distance(true);
        m_bNight = false;
        return;
    }

    if (fSpeed >= GetCaptureSpeedLimit())
    {
        // 화면에 속도 및 거리, REC 표시 출력
        displaySpeedDistance(fSpeed, fDistance, Qt::red, true);

        // HUD에 속도 및 거리, REC 표시 출력
        displayHudSpeedDistance(true, true, true, true);
    //    빨간색 테두리 표시 등
        displayRedOutline(true);
    //        이미지 또는 동영상을 설정대로 저장
        ImageVideoSave();
        //썸네일 표시 처리, 썸네일 위에 단속 정보 표시 처리 출력
        displayThumbnail(fSpeed, fDistance);
        sleep(1);
    }
    else if (fSpeed < GetCaptureSpeedLimit())
    {
//        화면에 속도 및 거리 출력
        displaySpeedDistance(fSpeed, fDistance, Qt::white, false);

//        HUD에 속도 및 거리 출력
        displayHudSpeedDistance(true, true, false, true);

        displayRedOutline(false);
//        로그 저장
    }
}

void EnforcementComponentWidget::on_showSpeedDistance(float fSpeed, float fDistance)
{
//    화면에 속도 및 거리 출력
    displaySpeedDistance(fSpeed, fDistance, Qt::white, false);
//        HUD에 속도 및 거리 출력
    displayHudSpeedDistance(true, true, false, true);

    displayRedOutline(false);
//        로그 저장

}

void EnforcementComponentWidget::on_showDistance(float fDistance, int nSensitivity)
{
//    화면에 거리 출력
    displayDistance(fDistance);
//	HUD에 거리 출력
    displayHudDistance(true, true);

    displayRedOutline(false);
//    로그 저장

}

void EnforcementComponentWidget::on_Night()
{
    m_bNight = true;
}

void EnforcementComponentWidget::on_STMode()
{
    m_UserModeOn = true;
    zoomRange();
}

void EnforcementComponentWidget::on_LTMode()
{
    m_UserModeOn = false;
    zoomRange();
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
        ui->bikePushButton->setDown(false);
        m_bBikeChecked = !m_bBikeChecked;
    }
    if (m_bTruckChecked)
    {
        m_bTruckChecked = !m_bTruckChecked;
        ui->truckPushButton->setDown(false);
    }
    else
    {
        m_bTruckChecked = !m_bTruckChecked;
        ui->truckPushButton->setDown(true);
    }
    setVehicleMode();
}


void EnforcementComponentWidget::on_bikePushButton_clicked()
{
    if (m_bTruckChecked)
    {
        ui->truckPushButton->setDown(false);
        m_bTruckChecked = !m_bTruckChecked;
    }
    if (m_bBikeChecked)
    {
        m_bBikeChecked = !m_bBikeChecked;
        ui->bikePushButton->setDown(false);
    }
    else
    {
        m_bBikeChecked = !m_bBikeChecked;
        ui->bikePushButton->setDown(true);
    }
    setVehicleMode();
}

