#include "CameraZoomFocusWidget.h"
#include "ui_CameraZoomFocusWidget.h"

#include <QHeaderView>
#include <QJsonArray>

#include "StringLoader.h"
#include "SpeedUnitManager.h"
#include "ConfigManager.h"
#include "SerialLaserManager.h"
#include "SerialPacket.h"

CameraZoomFocusWidget::CameraZoomFocusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraZoomFocusWidget)
{
    ui->setupUi(this);

    ui->zoomLabel->setText("Z: 2FCE");
    ui->focusLabel->setText("F: 1585");

    ui->optPushButton->setText(LoadString("IDS_OPT"));
    ui->focusPlusPushButton->setText(LoadString("IDS_FOCUS_PLIS"));
    ui->FocusMinusPushButton->setText(LoadString("IDS_FOCUS_MINUS"));

    ui->dayComboBox->addItem(LoadString("IDS_DAY"));
    ui->dayComboBox->addItem(LoadString("IDS_NIGHT"));

    ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
    ui->initPushButton->setText(LoadString("IDS_INIT"));

    ui->zoomRangePushButton->setText(LoadString("IDS_ZOOM_60_100"));
    ui->dzPlusPushButton->setText(LoadString("IDS_DZ_PLUS"));
    ui->dzMinusPushButton->setText(LoadString("IDS_DZ_MINUS"));

    ui->pgrsSavePushButton->setText(LoadString("IDS_PQRS_SAVE"));
    ui->jpgSavePushButton->setText(LoadString("IDS_JPG_SAVE"));

    ConfigManager con = ConfigManager("parameter_setting1.json");
    QJsonObject object = con.GetConfig();


    if (object["speed selection"].toInt() == 1)
        m_UserModeOn = true;
    else
        m_UserModeOn = false;

    ConfigManager config = ConfigManager("zoom_level.json");
    QJsonObject object2 = config.GetConfig();
    QJsonArray m_captureSpeed = object2["st mode meter dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_stmetervector.push_back(item.toString());
    }
    m_captureSpeed = object2["st mode feet dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_stfeetvector.push_back(item.toString());
    }
    m_captureSpeed = object2["lt mode meter dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_ltmetervector.push_back(item.toString());
    }
    m_captureSpeed = object2["lt mode feet dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_ltfeetvector.push_back(item.toString());
    }


//    ui->tableWidget->setColumnWidth(0, ui->pgrsSavePushButton->width() / 2);
//    ui->tableWidget->setColumnWidth(1, ui->pgrsSavePushButton->width() * 1.5);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList rowHeaders;
    rowHeaders.append(LoadString("IDS_DAY"));
    rowHeaders.append(LoadString("IDS_NIGHT"));
    ui->tableWidget->setHorizontalHeaderLabels(rowHeaders);

    QStringList columnHeaders;
    foreach (auto item, m_ltmetervector)
    {
        columnHeaders.append(item);
    }
    ui->tableWidget->setVerticalHeaderLabels(columnHeaders);

    m_serialViscaManager.connectVisca();

    if (m_pSerialLaserManager == nullptr)
        m_pSerialLaserManager = new SerialLaserManager;

    m_serialViscaManager.show_dzoomPosition();
    connect(m_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float,int)));
}

CameraZoomFocusWidget::~CameraZoomFocusWidget()
{
    delete m_pSerialLaserManager;
    m_serialViscaManager.close();
    delete ui;
}

void CameraZoomFocusWidget::SetCamera(Camera *camera)
{
    if (camera != nullptr)
        m_pCamera = camera;
}

void CameraZoomFocusWidget::ZoomRange()
{
    int zoom_index = 0;
    if (m_UserModeOn)
    {
        m_nStIndex++;
        if (m_nStIndex == m_stmetervector.size())
            m_nStIndex = 0;

        zoom_index = m_nStIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_stmetervector[m_nStIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_stfeetvector[m_nStIndex]+distanceValue());
        }
    }
    else
    {
        m_nLtIndex++;
        if (m_nLtIndex == m_ltmetervector.size())
            m_nLtIndex = 0;

        zoom_index = m_nLtIndex;
        if (distance() == meter)
        {
            ui->zoomRangePushButton->setText(m_ltmetervector[m_nLtIndex]+distanceValue());
        }
        else
        {
            ui->zoomRangePushButton->setText(m_ltfeetvector[m_nLtIndex]+distanceValue());
        }

    }

    SetLaserDetectionAreaDistance(zoom_index);
}

void CameraZoomFocusWidget::on_optPushButton_clicked()
{
    m_serialViscaManager.set_AF_one_push_trigger();
}


void CameraZoomFocusWidget::on_focusPlusPushButton_clicked()
{
    m_serialViscaManager.plus_focus();
}


void CameraZoomFocusWidget::on_FocusMinusPushButton_clicked()
{
    m_serialViscaManager.minus_focus();
}

void CameraZoomFocusWidget::on_dayComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        m_serialViscaManager.set_infrared_mode_off();
    }
    else
    {
        m_serialViscaManager.set_infrared_mode_on();
    }
}


void CameraZoomFocusWidget::on_initPushButton_clicked()
{
    setTableInit();
    setFocusEditJsonInit();
}

void CameraZoomFocusWidget::SetLaserDetectionAreaDistance(int zoom_index)
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

void CameraZoomFocusWidget::setTableInit()
{

}

void CameraZoomFocusWidget::setFocusEditJsonInit()
{
    ConfigManager config = ConfigManager("focus_edit.json");
    QJsonObject object = config.GetConfig();
    QJsonArray ar = {0, 0, 0, 0, 0, 0};
    object["lt day focus edit"] = ar;
    object["lt night focus edit"] = ar;
    config.SaveFile();
}

void CameraZoomFocusWidget::on_zoomRangePushButton_clicked()
{
    ZoomRange();
}


void CameraZoomFocusWidget::on_dzPlusPushButton_clicked()
{
    m_serialViscaManager.plus_dzoom();
}


void CameraZoomFocusWidget::on_dzMinusPushButton_clicked()
{
    m_serialViscaManager.minus_dzoom();
}

void CameraZoomFocusWidget::on_showDistance(float fDistance, int nSensitivity)
{
    ui->speedSensitivitylabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distanceValue() + "(" + QString::number(nSensitivity)+ ")");
}


void CameraZoomFocusWidget::on_jpgSavePushButton_clicked()
{

}


void CameraZoomFocusWidget::on_pgrsSavePushButton_clicked()
{

}


void CameraZoomFocusWidget::on_autoTriggerPushButton_toggled(bool checked)
{
    m_bATChecked = checked;
    if (!checked)
    {
        ui->autoTriggerPushButton->setStyleSheet("border-color: blue;");
        if (m_pSerialLaserManager == nullptr)
            m_pSerialLaserManager = new SerialLaserManager;
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
        if (m_pSerialLaserManager != nullptr)
        {
            delete m_pSerialLaserManager;
            m_pSerialLaserManager = nullptr;
        }

    }
}

