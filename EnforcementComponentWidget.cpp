#include "EnforcementComponentWidget.h"
#include "ui_EnforcementComponentWidget.h"

#include <QPainter>
#include <QJsonArray>

#include "StringLoader.h"
#include "camera.h"
#include "WidgetSize.h"
#include "HUDManager.h"
#include "SerialLaserManager.h"
#include "SerialViscaManager.h"


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
    ui->bikePushButton->setImage("enforcement", "bike.jpg");

    QJsonArray ar = m_object["capture speed"].toArray();

    ui->speedLabel->setText(QString("CS: %0%4\nT%2%4\nM%3%4").arg(ar[0].toString()).arg(ar[1].toString()).arg(ar[2].toString()).arg(SpeedUnitManager::GetInstance()->distance()));
    ui->speedLabel->setDisabled(true);


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

    ui->speedLabel->setSizePolicy(sp_retain);

    ui->enforcementCountLabel->setSizePolicy(sp_retain);
    ui->enforcementDistanceSpeedLabel->setSizePolicy(sp_retain);
    ui->enforcementTimeLabel->setSizePolicy(sp_retain);

    camInit();
    hudInit();
    laserInit();

    ConfigManager config = ConfigManager("zoom_level.json");
    object = config.GetConfig();


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
        if (m_nDistance == meter)
            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stmetervector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
        else
            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stfeetvector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
    }
    else
    {
        if (m_nDistance == meter)
            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltmetervector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
        else
            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltfeetvector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
    }
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
    if (m_UserModeOn)
    {
        if (m_nDistance == meter)
        {
            if (m_nStIndex < m_stmetervector.size() - 1)
            {
                m_nStIndex++;
                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stmetervector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
                SerialViscaManager serialViscaManager;
                serialViscaManager.dzoom(m_nStIndex);
            }
        }
        else
        {
            if (m_nStIndex < m_stfeetvector.size() - 1)
            {
                m_nStIndex++;
                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stfeetvector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
                SerialViscaManager serialViscaManager;
                serialViscaManager.dzoom(m_nStIndex);
            }

        }
    }
    else
    {
        if (m_nDistance == meter)
        {
            if (m_nLtIndex < m_ltmetervector.size() - 1)
            {
                m_nLtIndex++;
                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltmetervector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
                SerialViscaManager serialViscaManager;
                serialViscaManager.dzoom(m_nLtIndex);
            }

        }
        else
        {
            if (m_nLtIndex < m_ltfeetvector.size() - 1)
            {
                m_nLtIndex++;
                ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltfeetvector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
                SerialViscaManager serialViscaManager;
                serialViscaManager.dzoom(m_nLtIndex);
            }

        }
    }
}
void EnforcementComponentWidget::dzMinus()
{
    if (m_UserModeOn)
    {
        if (m_nStIndex != 0)
        {
            m_nStIndex--;
            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_stmetervector[m_nStIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
            SerialViscaManager serialViscaManager;
            serialViscaManager.dzoom(m_nStIndex);
        }
    }
    else
    {
        if (m_nLtIndex != 0)
        {
            m_nLtIndex--;
            ui->zoomRangePushButton->setText(QString("(%1 %2)").arg(m_ltmetervector[m_nLtIndex]).arg(SpeedUnitManager::GetInstance()->distance()));
            SerialViscaManager serialViscaManager;
            serialViscaManager.dzoom(m_nLtIndex);
        }
    }

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

    ui->speedLabel->hide();

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

    ui->speedLabel->show();

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
    ConfigManager config = ConfigManager("parameter_settings1.json");
    QJsonObject object = config.GetConfig();
    ConfigManager config2 = ConfigManager("parameter_settings2.json");
    QJsonObject object2 = config2.GetConfig();

    SerialLaserManager serialLaserManager;
    serialLaserManager.set_weather_mode(object2["weather selection"].toInt());
    serialLaserManager.set_AJamming_mode(object2["anti-jamming selection"].toInt());
    serialLaserManager.set_buzzer_mode(object2["buzzer selection"].toInt());

    serialLaserManager.set_detection_distance(object["speed_selection"].toInt());

    ConfigManager config3 = ConfigManager("parameter_enforcement.json");
    QJsonObject object3 = config3.GetConfig();

    bool nUserModeOn = true;
    if (object["speed selection"].toInt() == 2)
        nUserModeOn = false;

    int distance = 0, area = 0;
    switch (object3["zoom index"].toInt())
    {
    case 1:
    {
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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
        if (nUserModeOn)
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

    serialLaserManager.set_detection_area(distance);
    serialLaserManager.set_detection_area(area);

    int dn = object["day&night selection"].toInt();
    if (dn >= 0 && dn <=3)
        serialLaserManager.set_night_mode(1);
    else
        serialLaserManager.set_night_mode(0);
    serialLaserManager.set_speed_measure_mode(1);
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
        painter.drawLine(gap, gap, this->geometry().width() - 2 * gap, gap);
        painter.drawLine(gap, gap, gap, this->geometry().height());
        painter.drawLine(this->geometry().width() - gap, gap, this->geometry().width() - 2 * gap, this->geometry().height() - 2 * gap);
        painter.drawLine(gap, this->geometry().height() - 2 * gap, this->geometry().width() - 2 * gap, this->geometry().height() - 2 * gap);
    }
}

void EnforcementComponentWidget::on_zoomRangePushButton_clicked()
{
    dzPlus();
//    ConfigManager configmanager = ConfigManager("parameter_settings1.json");
//    QJsonObject object = configmanager.GetConfig();

//    if (object["speed selection"].toInt() == 1)
//    {

//    }
//    else
//    {

//    }

}

void EnforcementComponentWidget::on_readyPushButton_clicked()
{
    switch (m_nMode)
    {
    case Ready:
    {
        ui->readyPushButton->setText(LoadString("IDS_AT"));
        m_nMode = AT;
    }
        break;
    case AT:
    {
        ui->readyPushButton->setText(LoadString("IDS_Manual"));
        m_nMode = Manual;
    }
        break;
    case Manual:
    {
        ui->readyPushButton->setText(LoadString("IDS_Ready"));
        m_nMode = Ready;
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

