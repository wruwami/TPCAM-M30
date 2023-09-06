#include "CameraAlignWidget.h"
#include "ui_CameraAlignWidget.h"

#include <QJsonArray>
#include <QPainter>
#include <QDebug>

#include "StringLoader.h"

#include "CustomPushButton.h"
#include "HUDManager.h"
#include "SerialLaserManager.h"
#include "SerialPacket.h"
#include "SpeedUnitManager.h"

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
    m_pSaveButton = ui->savePushButton;
    m_pCancelButton = ui->cancelPushButton;

    m_object = m_configManager.GetConfig();
    QJsonArray ar = m_object["HUD reticle pos"].toArray();
    m_HUDPoint = QPoint(ar[0].toInt() - HUD_x, ar[1].toInt() - HUD_y);
    ar = m_object["Camera reticle pos"].toArray();
    m_LaserPoint = QPoint(ar[0].toInt() - Laser_x, ar[1].toInt() - Laser_y);

    m_CameraMoveUnit = m_object["Camera reticle move unit"].toString().toInt();
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
        if ((m_HUDPoint.x() + x) > HUD_x || (m_HUDPoint.x() + x) < -HUD_x)
            return;
        if ((m_HUDPoint.y() + y) > HUD_y || (m_HUDPoint.y() + y) < -HUD_y)
            return;

        HUDManager hud;
        m_HUDPoint.setX(m_HUDPoint.x() + x);
        m_HUDPoint.setY(m_HUDPoint.y() + y);
        hud.SetPointX(m_HUDPoint.x());
        hud.SetPointX(m_HUDPoint.y());
        SetHudMode();
    }
    else
    {
        if ((m_LaserPoint.x() + m_CameraMoveUnit * x) > Laser_x || (m_LaserPoint.x() + m_CameraMoveUnit* x) < -Laser_x)
            return;
        if ((m_LaserPoint.y() + m_CameraMoveUnit * y) > Laser_y || (m_LaserPoint.y() + m_CameraMoveUnit * y) < -Laser_y)
            return;
        m_LaserPoint.setX(m_LaserPoint.x() + m_CameraMoveUnit * x);
        m_LaserPoint.setY(m_LaserPoint.y() + m_CameraMoveUnit * y);
        SetLaserMode();
    }
}

void CameraAlignWidget::setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager)
{
    m_pSerialLaserManager = newPSerialLaserManager;
}

void CameraAlignWidget::on_hudPushButton_clicked()
{
    if (m_bCameraChecked)
    {
        ui->cameraPushButton->setStyleSheet("border-color: blue;");
        ui->hudPushButton->setStyleSheet("border-color: red;");
//        ui->cameraPushButton->setDown(false);
        m_bCameraChecked = false;
//        ui->hudPushButton->setDown(true);
        m_bHUDChecked = true;
        SetHudMode();

         m_nMode = HUD;
    }
}


void CameraAlignWidget::on_cameraPushButton_clicked()
{
    if (m_bHUDChecked)
    {
        ui->cameraPushButton->setStyleSheet("border-color: red;");
        ui->hudPushButton->setStyleSheet("border-color: blue;");
        m_bHUDChecked = false;
//        ui->cameraPushButton->setDown(true);
        m_bCameraChecked = true;
        SetLaserMode();
        m_nMode = Laser;
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
    ar.insert(0, m_HUDPoint.x() + HUD_x);
    ar.insert(1, m_HUDPoint.y() + HUD_y);

    m_object["HUD reticle pos"] = ar;

    QJsonArray ar2;
    ar2.insert(0, m_LaserPoint.x() + Laser_x);
    ar2.insert(1, m_LaserPoint.y() + Laser_y);

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
//    ui->autoTriggerPushButton->setDown(checked);
//    ui->autoTriggerPushButton->setChecked(checked);
    if (!checked)
    {
        ui->autoTriggerPushButton->setStyleSheet("border-color: blue;");
        m_pSerialLaserManager->start_laser();
        m_pSerialLaserManager->request_distance(true);

        SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
        connect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float,int)));
    }
    else
    {
        ui->autoTriggerPushButton->setStyleSheet("border-color: red;");
        SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
        disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float,int)));

        m_pSerialLaserManager->stop_laser();
        m_pSerialLaserManager->request_distance(false);
    }
}

void CameraAlignWidget::on_showDistance(float fDistance, int nSensitivity)
{
    ui->speedSensitivitylabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distanceValue() + "(" + QString::number(nSensitivity)+ ")");
}

void CameraAlignWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPen crossPen(Qt::white);
    crossPen.setStyle(Qt::SolidLine);
//        crossPen.setWidth(10);
//        QRect rect = QRect(width() / 2, height() / 2 + 10, 10, 30);
//        QRect rect2 = QRect(width() / 2 - 10, height() / 2, 10, 30);
    if (m_bHUDChecked)
    {
        int gap = 10;

        int x = m_HUDPoint.x();
        int y = m_HUDPoint.y();
        QRect rect = QRect(QPoint(((width() / 2 ) + x) - 3 * gap, ((height() / 2) + y) - gap), QPoint(((width() / 2) + x) + 3*gap, ((height() / 2) + y) + gap));
        QRect rect2 = QRect(QPoint(((width() / 2) + x) - gap, ((height() / 2) + y) - 3 * gap), QPoint(((width() / 2) + x) + gap, ((height() / 2) + y) + 3 * gap));

        painter.fillRect(rect, Qt::white);
        painter.fillRect(rect2, Qt::white);
    }
    else if (m_bCameraChecked)
    {
        int gap = 10;

        int x = m_LaserPoint.x();
        int y = m_LaserPoint.y();

        qDebug() << x;
        qDebug() << y;

        QRect rect = QRect(QPoint(((width() / 2 ) + x) - 3 * gap, ((height() / 2) + y) - gap), QPoint(((width() / 2) + x) + 3*gap, ((height() / 2) + y) + gap));
        QRect rect2 = QRect(QPoint(((width() / 2) + x) - gap, ((height() / 2) + y) - 3 * gap), QPoint(((width() / 2) + x) + gap, ((height() / 2) + y) + 3 * gap));

        painter.fillRect(rect, Qt::white);
        painter.fillRect(rect2, Qt::white);
    }

}
