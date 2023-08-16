#include "CameraZoomFocusWidget.h"
#include "ui_CameraZoomFocusWidget.h"

#include <QHeaderView>
#include <QJsonArray>

#include "StringLoader.h"
#include "SpeedUnitManager.h"
#include "ConfigManager.h"
#include "SerialLaserManager.h"
#include "SerialPacket.h"
#include "ViscaPacket.h"
#include "FileManager.h"
#include "camera.h"

CameraZoomFocusWidget::CameraZoomFocusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraZoomFocusWidget)
{
    ui->setupUi(this);

//    ui->zoomLabel->setText("Z: 2FCE");
//    ui->focusLabel->setText("F: 1585");

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

    ui->autoTriggerPushButton->setEnabled(true);

    ConfigManager con = ConfigManager("parameter_setting1.json");
    QJsonObject object = con.GetConfig();


    if (object["speed selection"].toInt() == 1)
        m_UserModeOn = true;
    else
        m_UserModeOn = false;

    ConfigManager config = ConfigManager("zoom_level.json");
    QJsonObject object2 = config.GetConfig();
    QJsonArray m_captureSpeed = object2["st mode meter dist"].toArray();
    m_captureSpeed = object2["lt mode meter dist"].toArray();
    foreach(auto item, m_captureSpeed)
    {
        m_ltmetervector.push_back(item.toString());
    }
    m_captureSpeed = object2["lt mode feet dist"].toArray();

    m_object2 = m_coofigManager2.GetConfig();
    m_object3 = m_coofigManager3.GetConfig();


//    ui->tableWidget->setColumnWidth(0, ui->pgrsSavePushButton->width() / 2);
//    ui->tableWidget->setColumnWidth(1, ui->pgrsSavePushButton->width() * 1.5);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList rowHeaders;
    rowHeaders.append(LoadString("IDS_DAY"));
    rowHeaders.append(LoadString("IDS_NIGHT"));
    ui->tableWidget->setHorizontalHeaderLabels(rowHeaders);

    QStringList columnHeaders;
//    foreach (auto item, m_ltmetervector)
//    {
//        columnHeaders.append(item);
//    }
    columnHeaders.append(LoadString("IDS_Z10_36"));
    columnHeaders.append(LoadString("IDS_Z36_60"));
    columnHeaders.append(LoadString("IDS_Z60_100"));
    columnHeaders.append(LoadString("IDS_Z100_160"));
    columnHeaders.append(LoadString("IDS_Z160"));
    columnHeaders.append(LoadString("IDS_Z260"));
    ui->tableWidget->setVerticalHeaderLabels(columnHeaders);
    ui->pgrsSavePushButton->setDisabled(true);

    m_nTableIndex = QPoint(0,0);
    m_object = config.GetConfig();

    setTableInit();

//    m_serialViscaManager.connectVisca();

//    if (m_pSerialLaserManager == nullptr)
//        m_pSerialLaserManager = new SerialLaserManager;

    m_pSerialViscaManager->show_dzoomPosition();

    connect(m_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_dzoom(QString)), this, SLOT(on_show_dzoom(QString)));
    connect(m_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_zoom(QString)), this, SLOT(on_show_zoom(QString)));
    connect(m_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_focus(QString)), this, SLOT(on_show_focus(QString)));

    SendViscaValue();
}

CameraZoomFocusWidget::~CameraZoomFocusWidget()
{
    disconnect(m_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_dzoom(QString)), this, SLOT(on_show_dzoom(QString)));
    disconnect(m_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_zoom(QString)), this, SLOT(on_show_zoom(QString)));
    disconnect(m_pSerialViscaManager->getVisca_packet(), SIGNAL(sig_show_focus(QString)), this, SLOT(on_show_focus(QString)));

//    delete m_pSerialLaserManager;
//    m_serialViscaManager.close();
    delete ui;
}

void CameraZoomFocusWidget::SetCamera(Camera *camera)
{
    if (camera != nullptr)
        m_pCamera = camera;
}

void CameraZoomFocusWidget::setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager)
{
    m_pSerialLaserManager = newPSerialLaserManager;

    connect(m_pSerialLaserManager->getLaser_packet(), SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float,int)));
}

void CameraZoomFocusWidget::ZoomRange()
{
    int zoom_index = 0;
    m_nLtIndex++;
    m_nTableIndex.setY(m_nLtIndex);
    if (m_nLtIndex == m_ltmetervector.size())
        m_nLtIndex = 0;

    zoom_index = m_nLtIndex;
    ui->zoomRangePushButton->setText(m_ltmetervector[m_nLtIndex]+distanceValue());

    SetLaserDetectionAreaDistance(zoom_index);

    if (m_mTableStatus[std::make_pair(m_nTableIndex.x(), m_nTableIndex.y())] == 1)
        ui->pgrsSavePushButton->setDisabled(false);
    else
        ui->pgrsSavePushButton->setDisabled(true);
}

void CameraZoomFocusWidget::on_optPushButton_clicked()
{
    m_pSerialViscaManager->set_AF_one_push_trigger();
}


void CameraZoomFocusWidget::on_focusPlusPushButton_clicked()
{
    m_pSerialViscaManager->plus_focus();
}


void CameraZoomFocusWidget::on_FocusMinusPushButton_clicked()
{
    m_pSerialViscaManager->minus_focus();
}

void CameraZoomFocusWidget::on_dayComboBox_currentIndexChanged(int index)
{
    m_nTableIndex.setX(index);
    QJsonObject object;
    if (index == 0)
    {
        m_pSerialViscaManager->set_infrared_mode_off();
        object = m_object["Day"].toObject()["Normal"].toObject();
    }
    else
    {
        m_pSerialViscaManager->set_infrared_mode_on();
        object = m_object["Night"].toObject()["Normal"].toObject();
    }
    m_pSerialViscaManager->set_AE_Mode(object["priority"].toString());
    m_pSerialViscaManager->set_iris(object["Iris"].toInt());
    m_pSerialViscaManager->set_shutter_speed(object["Shutter"].toInt());
    m_pSerialViscaManager->set_gain(object["Gain"].toInt());
    m_pSerialViscaManager->set_noise_reduction_on(object["DNR"].toString());
    object["DIS"].toBool() ? m_pSerialViscaManager->set_DIS_on() : m_pSerialViscaManager->set_DIS_off();
    object["DEFOG"].toBool() ? m_pSerialViscaManager->set_defog_on() : m_pSerialViscaManager->set_defog_off();
    object["HLC"].toBool() ? m_pSerialViscaManager->set_HLC_on() : m_pSerialViscaManager->set_HLC_off();

    if (m_mTableStatus[std::make_pair(m_nTableIndex.x(), m_nTableIndex.y())] == 1)
        ui->pgrsSavePushButton->setDisabled(false);
    else
        ui->pgrsSavePushButton->setDisabled(true);

    SendViscaValue();
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
    QJsonArray ar = m_object3["lt day focus"].toArray();
    for (int i = 0; i < ar.size(); i++ )
    {
        QTableWidgetItem item(ar[i].toString());
        ui->tableWidget->setItem(i, 0, &item);
    }

    ar = m_object3["lt night focus"].toArray();
    for (int i = 0; i < ar.size(); i++ )
    {
        QTableWidgetItem item(ar[i].toString());
        ui->tableWidget->setItem(i, 1, &item);
    }

}

void CameraZoomFocusWidget::setFocusEditJsonInit()
{
    ConfigManager config = ConfigManager("focus_edit.json");
    QJsonObject object = config.GetConfig();
    QJsonArray ar = {0, 0, 0, 0, 0, 0};
    object["lt day focus edit"] = ar;
    object["lt night focus edit"] = ar;
    config.SaveFile();

    ui->tableWidget->clearContents();
}

void CameraZoomFocusWidget::SetFocusLabel()
{
    ui->focusLabel->setText(QString("F:%1\nDZ:%2").arg(m_strFocus, m_strDZoom));
}

void CameraZoomFocusWidget::SaveJpg()
{
    QString filename = GetSubPath("manual_capture", SD) + "/" + GetFileName(SC);

    QPixmap pixmap = m_pCamera->grab();
    pixmap.save(filename);
//    m_pCamera->SaveImage(filename);
}

void CameraZoomFocusWidget::ModifyFocusEditJson(int x, int y, int value)
{
    ConfigManager config = ConfigManager("focus_edit.json");
    QJsonObject object = config.GetConfig();
    QJsonArray ar = object["lt day focus edit"].toArray();
    QJsonArray ar2 = object["lt night focus edit"].toArray();
    if (x == 0)
        ar[y] = value;
    else
        ar2[y] = value;

    object["lt day focus edit"] = ar;
    object["lt night focus edit"] = ar2;

    config.SaveFile();

    ui->tableWidget->clearContents();

}

void CameraZoomFocusWidget::SaveFocusJson()
{
    ConfigManager config = ConfigManager("focus.json");
    QJsonObject object = config.GetConfig();
    QJsonArray ar = object["lt day focus"].toArray();
    QJsonArray ar2 = object["lt night focus"].toArray();
    QJsonArray ar3 = object["st day focus"].toArray();
    QJsonArray ar4 = object["st night focus"].toArray();

    if (m_nTableIndex.x() == 0)
    {
        ar[m_nTableIndex.y()] = m_strFocus;
        SetLtValue(m_nTableIndex.y(), ar, ar3);
    }
    else
    {
        ar2[m_nTableIndex.y()] = m_strFocus;
        SetLtValue(m_nTableIndex.y(), ar2, ar4);
    }

    object["lt day focus"] = ar;
    object["lt night focus"] = ar2;
    object["st day focus"] = ar3;
    object["st night focus"] = ar4;

    config.SaveFile();

}

void CameraZoomFocusWidget::SetLtValue(int index, QJsonArray& ar, QJsonArray& ar2)
{
    int A = (ar[5].toInt() - ar[4].toInt()) / 5;

    switch(index)
    {
    case 0:
    {
        ar2[0] = ar[index];
    }
        break;
    case 1:
    {
        ar2[1] = ar[index];

    }
        break;
    case 2:
    {
        ar2[2] = ar[index];
        ar2[3] = ar[index];

    }
        break;
    case 3:
    {
        ar2[4] = ar[index];
        ar2[5] = ar[index];
        ar2[6] = ar[index];

    }
        break;
    case 4:
    {
        ar2[7] = ar[index];
        ar2[8] = QString::number(ar[index].toInt() + A, 16);
        ar2[9] = QString::number(ar[index].toInt() + A, 16);
        ar2[10] = QString::number(ar[index].toInt() + A, 16);
        ar2[11] = QString::number(ar[index].toInt() + A, 16);
    }
        break;
    case 5:
    {
        ar2[12] = ar[index];
    }
        break;
    }
}

void CameraZoomFocusWidget::SendViscaValue()
{
    m_pSerialViscaManager->show_dzoomPosition();
    m_pSerialViscaManager->show_zoomPosition();
    m_pSerialViscaManager->show_focusPosition();
}

void CameraZoomFocusWidget::on_zoomRangePushButton_clicked()
{
    ZoomRange();
    SendViscaValue();
}


void CameraZoomFocusWidget::on_dzPlusPushButton_clicked()
{
    m_pSerialViscaManager->plus_dzoom();
}


void CameraZoomFocusWidget::on_dzMinusPushButton_clicked()
{
    m_pSerialViscaManager->minus_dzoom();
}

void CameraZoomFocusWidget::on_showDistance(float fDistance, int nSensitivity)
{
    ui->speedSensitivitylabel->setText(QString::number(getDistanceValue(fDistance), 'f', 1) + distanceValue() + "(" + QString::number(nSensitivity)+ ")");
}


void CameraZoomFocusWidget::on_jpgSavePushButton_clicked()
{

    QTableWidgetItem* item = ui->tableWidget->item(m_nTableIndex.x(), m_nTableIndex.y());
    item->setTextColor(Qt::red);
    ui->tableWidget->setItem(m_nTableIndex.x(), m_nTableIndex.y(), item);
    SaveJpg();

    m_mTableStatus[std::make_pair(m_nTableIndex.x(), m_nTableIndex.y())] = 1;
}


void CameraZoomFocusWidget::on_pgrsSavePushButton_clicked()
{
    QTableWidgetItem* item = ui->tableWidget->item(m_nTableIndex.x(), m_nTableIndex.y());
    item->setTextColor(Qt::green);
    ui->tableWidget->setItem(m_nTableIndex.x(), m_nTableIndex.y(), item);

    ModifyFocusEditJson(m_nTableIndex.x(), m_nTableIndex.y());

    m_mTableStatus[std::make_pair(m_nTableIndex.x(), m_nTableIndex.y())] = 2;

    SaveFocusJson();
}


//void CameraZoomFocusWidget::on_autoTriggerPushButton_toggled(bool checked)
//{
//    m_bATChecked = checked;
//    if (!checked)
//    {
//        ui->autoTriggerPushButton->setStyleSheet("border-color: blue;");
//        m_pSerialLaserManager->start_laser();
//        m_pSerialLaserManager->request_distance(true);

//        SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
//        connect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float,int)));
//    }
//    else
//    {
//        ui->autoTriggerPushButton->setStyleSheet("border-color: red;");
//        SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();
//        disconnect(laser_packet, SIGNAL(sig_showDistance(float,int)), this, SLOT(on_showDistance(float,int)));

//        m_pSerialLaserManager->stop_laser();
//        m_pSerialLaserManager->request_distance(false);

//    }
//}

void CameraZoomFocusWidget::on_show_zoom(QString zoom)
{
//    ui->zoomLabel->
    ui->zoomLabel->setText("\nZ:"+zoom);
}

void CameraZoomFocusWidget::on_show_focus(QString focus)
{
//    ui->focusLabel->setText("F:"+focus);
    m_strFocus = focus;
    QTableWidgetItem item(focus);
    ui->tableWidget->setItem(m_nTableIndex.x(), m_nTableIndex.y(), &item);
}

void CameraZoomFocusWidget::on_show_dzoom(QString dzoom)
{
//    ui->focusLabel->setText("DZ:"+dzoom);
    m_strDZoom = dzoom;
}


void CameraZoomFocusWidget::on_autoTriggerPushButton_clicked(bool checked)
{
    if (checked)
    {
        ui->autoTriggerPushButton->setStyleSheet("border-color: red;");
        m_pSerialLaserManager->start_laser();
        m_pSerialLaserManager->request_distance(true);

    }
    else
    {
        ui->autoTriggerPushButton->setStyleSheet("border-color: blue;");
        m_pSerialLaserManager->stop_laser();
        m_pSerialLaserManager->request_distance(false);
    }

//    SerialPacket* laser_packet = m_pSerialLaserManager->getLaser_packet();

}

void CameraZoomFocusWidget::setPSerialViscaManager(SerialViscaManager *newPSerialViscaManager)
{
    m_pSerialViscaManager = newPSerialViscaManager;
}

