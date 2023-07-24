#include "CameraAlignWidget.h"
#include "ui_CameraAlignWidget.h"

#include <QJsonArray>

#include "StringLoader.h"

#include "CustomPushButton.h"
#include "HUDManager.h"

CameraAlignWidget::CameraAlignWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAlignWidget)
{
    ui->setupUi(this);

    ui->homePushButton->setText(LoadString("IDS_HOME"));
    ui->defaultPushButton->setText(LoadString("IDS_DEFAULT"));
    ui->autoTriggerPushButton->setText(LoadString("IDS_AUTO_TRIGGER"));
    ui->hudPushButton->setText(LoadString("IDS_HUD"));
    ui->upPushButton->setText(LoadString("IDS_UP"));
    ui->leftPushButton->setText(LoadString("IDS_LEFT"));
    ui->rightPushButton->setText(LoadString("IDS_RIGHT"));
    ui->downPushButton->setText(LoadString("IDS_DOWN"));
    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cameraPushButton->setText(LoadString("IDS_CAMERA"));

    ui->hudPushButton->setCheckable(true);
    ui->cameraPushButton->setCheckable(true);
    ui->autoTriggerPushButton->setCheckable(true);

    ui->hudPushButton->setDown(true);

    m_pHomeButton = ui->homePushButton;

    m_object = m_configManager.GetConfig();
    QJsonArray ar = m_object["HUD reticle pos"].toArray();
    m_HUDPoint = QPoint(ar[0].toInt(), ar[1].toInt());
    ar = m_object["Camera reticle pos"].toArray();
    m_LaserPoint = QPoint(ar[0].toInt(), ar[1].toInt());
}

CameraAlignWidget::~CameraAlignWidget()
{
    delete ui;
}

void CameraAlignWidget::SetCamera(Camera *camera)
{
    if (camera != nullptr)
        m_pCamera = camera;
}

void CameraAlignWidget::SetHudMode()
{
    ui->hudLabel->setText(LoadString("IDS_HUD") +"[" +QString("%1").arg(QString::number(m_HUDPoint.x()), 2) + "," + QString("%1").arg(QString::number(m_HUDPoint.y()), 2) + "]");
}

void CameraAlignWidget::SetLaserMode()
{
    ui->hudLabel->setText(LoadString("IDS_LASER") +"[" +QString("%1").arg(QString::number(m_LaserPoint.x()), 2) + "," + QString("%1").arg(QString::number(m_LaserPoint.y()), 2) + "]");
}

void CameraAlignWidget::SetDirection(int x, int y)
{
    if (m_nMode == HUD)
    {
        HUDManager hud;
        m_HUDPoint.setX(m_HUDPoint.x() + x);
        m_HUDPoint.setY(m_HUDPoint.y() + y);
        hud.SetPointX(m_HUDPoint.x());
        hud.SetPointX(m_HUDPoint.y());
        SetHudMode();
    }
    else
    {
        m_LaserPoint.setX(m_LaserPoint.x() + x);
        m_LaserPoint.setY(m_LaserPoint.y() + y);
        SetLaserMode();
    }
}

void CameraAlignWidget::on_hudPushButton_clicked()
{
    if (m_bCameraChecked)
    {
        ui->cameraPushButton->setDown(false);
        m_bCameraChecked = false;
        ui->hudPushButton->setDown(true);
        m_bHUDChecked = true;
        SetHudMode();
    }
}


void CameraAlignWidget::on_cameraPushButton_clicked()
{
    if (m_bHUDChecked)
    {
        ui->hudPushButton->setDown(false);
        m_bHUDChecked = false;
        ui->cameraPushButton->setDown(true);
        m_bCameraChecked = true;
        SetLaserMode();
    }

}


void CameraAlignWidget::on_leftPushButton_clicked()
{
    SetDirection(-1, 0);
}


void CameraAlignWidget::on_rightPushButton_clicked()
{
    SetDirection(1, 0);
}


void CameraAlignWidget::on_savePushButton_clicked()
{
    QJsonArray ar;
    ar.insert(0, m_HUDPoint.x());
    ar.insert(1, m_HUDPoint.y());

    m_object["HUD reticle pos"] = ar;

    QJsonArray ar2;
    ar2.insert(0, m_LaserPoint.x());
    ar2.insert(1, m_LaserPoint.y());

    m_object["Camera reticle pos"] = ar2;

    m_configManager.SetConfig(m_object);
}


void CameraAlignWidget::on_downPushButton_clicked()
{
    SetDirection(0, 1);
}


void CameraAlignWidget::on_defaultPushButton_clicked()
{
    m_HUDPoint = QPoint(DefaultHUDValue::HUD_x, DefaultHUDValue::HUD_y);
    m_LaserPoint = QPoint(DefaultLaserValue::Laser_x, DefaultLaserValue::Laser_y);
    HUDManager hudManager;
    hudManager.HUDInit();
}


void CameraAlignWidget::on_upPushButton_clicked()
{
    SetDirection(0, -1);
}


void CameraAlignWidget::on_autoTriggerPushButton_toggled(bool checked)
{
    ui->autoTriggerPushButton->setDown(checked);
}

