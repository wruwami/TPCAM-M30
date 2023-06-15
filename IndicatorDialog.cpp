#include "IndicatorDialog.h"
#include "ui_IndicatorDialog.h"
#include "CustomPushButton.h"
#include <stdlib.h>

#include <QFile>
#include <QPainter>
#include <QDateTime>
#include "qdir.h"

#include "BaseDialog.h"
#include "Color.h"
#include "WidgetSize.h"
#include "StringLoader.h"

#include "IndicatorCameraExposeWidget.h"
#include "IndicatorCameraFocusWidget.h"

#include <QGraphicsOpacityEffect>
#include "WidgetSize.h"
#include "FileManager.h"
#include "ConfigManager.h"
#include "MainMenuWidget.h"

IndicatorDialog::IndicatorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
//    setStyleSheet(".QDialog{background-color: rgba(256,256,256,127); border:none;}");
//    auto qgoEffect = new QGraphicsOpacityEffect(this);
//    qgoEffect->setOpacity(0.5);
//    setGraphicsEffect(qgoEffect);
//    setAutoFillBackground(true);

    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 960)));

//    ui->screenRecordingPushButton->setImage("indicator", "screen_recording.jpg");
//    ui->onPushButton->setImage("indicator", "screen_recording_on.jpg");
//    ui->offPushButton->setImage("indicator", "screen_recording_off.jpg");

    ui->screenRecordingPushButton->setVisible(true);
//    ui->onPushButton->setVisible(false);
//    ui->offPushButton->setVisible(false);

    m_serialViscaManager.connectVisca();
    m_serialLaserManager.connectLaser();

    initlize();
}

IndicatorDialog::~IndicatorDialog()
{
    m_serialLaserManager.close();
    m_serialViscaManager.close();

    m_configManager1.SetConfig(m_jsonObject1);
    m_configManager1.SaveFile();

    m_configManager2.SetConfig(m_jsonObject1);
    m_configManager2.SaveFile();

//    if (m_pIndicatorCameraFocusWidget != nullptr)
//        delete m_pIndicatorCameraFocusWidget;

//    if (m_pIndicatorCameraExposeWidget != nullptr)
//        delete m_pIndicatorCameraExposeWidget;

    delete ui;
}

void IndicatorDialog::setFocusExposeDisabled(bool isDisable)
{
    if (m_pCameraExposePushButton != nullptr)
        m_pCameraExposePushButton->setDisabled(isDisable);

    if (m_pCameraFocusPushButton != nullptr)
        m_pCameraFocusPushButton->setDisabled(isDisable);
}

bool IndicatorDialog::GetGPSStatus()
{
    return true;
}

bool IndicatorDialog::GetWifiStatus()
{
    return false;
}

void IndicatorDialog::SetMainMenu(MainMenuWidget *mainMenuWidgt)
{
    m_pMainMenuWidget = mainMenuWidgt;
}

void IndicatorDialog::on_cameraPushButton_clicked()
{
    clearSecondRow();

    m_pCameraExposePushButton = new CustomPushButton;
    m_pCameraFocusPushButton = new CustomPushButton;

    m_pCameraExposePushButton->setText(LoadString("IDS_EXPOSE"));
    m_pCameraFocusPushButton->setText(LoadString("IDS_FOCUS"));

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(0));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->insertWidget(0, m_pCameraExposePushButton, 2);
    ui->horizontalLayout2->insertWidget(1, m_pCameraFocusPushButton, 2);

    setFocusExposeDisabled(m_bFocusExposeDisabled);

    QObject::connect((QWidget*)m_pCameraExposePushButton, SIGNAL(clicked()), this, SLOT(on_cameraExposeClicked()));
    QObject::connect((QWidget*)m_pCameraFocusPushButton, SIGNAL(clicked()), this, SLOT(on_cameraFocusClicked()));
}



void IndicatorDialog::on_daynNightPushButton_clicked()
{
    clearSecondRow();
    m_pDay1PushButton = new CustomPushButton;
    m_pDay2PushButton = new CustomPushButton;
    m_pDay3PushButton = new CustomPushButton;
    m_pNight1PushButton = new CustomPushButton;
    m_pNight2PushButton = new CustomPushButton;
    m_pNight3PushButton = new CustomPushButton;
    m_pDay1PushButton->setImage("indicator", "day1.jpg");
    m_pDay2PushButton->setImage("indicator", "day2.jpg");
    m_pDay3PushButton->setImage("indicator", "day3.jpg");
    m_pNight1PushButton->setImage("indicator", "night1.jpg");
    m_pNight2PushButton->setImage("indicator", "night2.jpg");
    m_pNight3PushButton->setImage("indicator", "night3.jpg");

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(0));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(5));
    ui->horizontalLayout2->insertWidget(0, m_pDay1PushButton, 6);
    ui->horizontalLayout2->insertWidget(1, m_pDay2PushButton, 6);
    ui->horizontalLayout2->insertWidget(2, m_pDay3PushButton, 6);
    ui->horizontalLayout2->insertWidget(3, m_pNight1PushButton, 6);
    ui->horizontalLayout2->insertWidget(4, m_pNight2PushButton, 6);
    ui->horizontalLayout2->insertWidget(5, m_pNight3PushButton, 6);

    connect(m_pDay1PushButton, SIGNAL(clicked()), this, SLOT(on_day1WidgetClicked()));
    connect(m_pDay2PushButton, SIGNAL(clicked()), this, SLOT(on_day2WidgetClicked()));
    connect(m_pDay3PushButton, SIGNAL(clicked()), this, SLOT(on_day3WidgetClicked()));
    connect(m_pNight1PushButton, SIGNAL(clicked()), this, SLOT(on_night1WidgetClicked()));
    connect(m_pNight2PushButton, SIGNAL(clicked()), this, SLOT(on_night2WidgetClicked()));
    connect(m_pNight3PushButton, SIGNAL(clicked()), this, SLOT(on_night3WidgetClicked()));
}

void IndicatorDialog::on_gpsPushButton_clicked()
{
//    clearSecondRow();
    BaseDialog baseDialog(Dialog::IndicatorGPSWidgetType, Qt::AlignmentFlag::AlignCenter, "", true);
    baseDialog.exec();

}

void IndicatorDialog::on_comPushButton_clicked()
{
    clearSecondRow();
    m_pWifiPushButton = new CustomPushButton();
    m_pBTPushButton = new CustomPushButton();
    m_pEthernetPushButton = new CustomPushButton();
    m_pWifiPushButton->setImage("indicator", "indicator_wifi_connected.jpg");
    m_pBTPushButton->setImage("indicator", "BT.jpg");
    m_pEthernetPushButton->setImage("indicator", "ethernet.png");

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(6));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(5));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->addWidget(m_pWifiPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pBTPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pEthernetPushButton, 2);
}

void IndicatorDialog::on_speedPushButton_clicked()
{
    clearSecondRow();
    m_pSTPushButton = new CustomPushButton();
    m_pLTPushButton = new CustomPushButton();
    m_pSTPushButton->setImage("indicator", "indicator_enable_user_mode_on.jpg");
    m_pLTPushButton->setImage("indicator", "indicator_enable_user_mode_off.jpg");

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->insertWidget(3, m_pSTPushButton, 2);
    ui->horizontalLayout2->insertWidget(4, m_pLTPushButton , 2);
    ui->horizontalLayout2->setStretch(6, 1);

    connect(m_pSTPushButton, SIGNAL(clicked()), this, SLOT(on_speedSTPushButton_clicked()));
    connect(m_pLTPushButton, SIGNAL(clicked()), this, SLOT(on_speedLTPushButton_clicked()));

}

void IndicatorDialog::on_speedSTPushButton_clicked()
{
    ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_on.jpg");
    m_jsonObject1["speed selection"] = 1;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pSpeedPushbutton, "indicator", "indicator_enable_user_mode_on.jpg");
}

void IndicatorDialog::on_speedLTPushButton_clicked()
{
    ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_off.jpg");
    m_jsonObject1["speed selection"] = 2;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pSpeedPushbutton, "indicator", "indicator_enable_user_mode_off.jpg");
}

void IndicatorDialog::on_enforcementPushButton_clicked()
{
    clearSecondRow();
    m_pImagePushButton = new CustomPushButton();
    m_pVideoPushButton = new CustomPushButton();
    m_pImageVideoPushButton = new CustomPushButton();
    m_pImagePushButton->setImage("indicator", "indicator_mode_i.jpg");
    m_pVideoPushButton->setImage("indicator", "indicator_mode_v.jpg");
    m_pImageVideoPushButton->setImage("indicator", "indicator_mode_a.jpg");

//    ui->gridLayout->setColumnStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));

    ui->horizontalLayout2->insertWidget(2, m_pImagePushButton, 2);
    ui->horizontalLayout2->insertWidget(3, m_pImageVideoPushButton , 2);
    ui->horizontalLayout2->insertWidget(4, m_pVideoPushButton , 2);

    connect(m_pImagePushButton, SIGNAL(clicked()), this, SLOT(on_enforcementIPushButton_clicked()));
    connect(m_pVideoPushButton, SIGNAL(clicked()), this, SLOT(on_enforcementVPushButton_clicked()));
    connect(m_pImageVideoPushButton, SIGNAL(clicked()), this, SLOT(on_enforcementAPushButton_clicked()));
}

void IndicatorDialog::on_enforcementIPushButton_clicked()
{
    ui->enforcementPushButton->setImage("indicator", "indicator_mode_i.jpg");
    m_jsonObject1["enforcement selection"] = 1;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pEnforcementPushbutton, "indicator", "indicator_mode_i.jpg");
}

void IndicatorDialog::on_enforcementAPushButton_clicked()
{
    ui->enforcementPushButton->setImage("indicator", "indicator_mode_a.jpg");
    m_jsonObject1["enforcement selection"] = 2;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pEnforcementPushbutton, "indicator", "indicator_mode_a.jpg");
}

void IndicatorDialog::on_enforcementVPushButton_clicked()
{
    ui->enforcementPushButton->setImage("indicator", "indicator_mode_v.jpg");
    m_jsonObject1["enforcement selection"] = 3;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pEnforcementPushbutton, "indicator", "indicator_mode_v.jpg");
}

void IndicatorDialog::on_weatherPushButton_clicked()
{
    clearSecondRow();
    m_pSunnyPushButton = new CustomPushButton();
    m_pRainyPushButton = new CustomPushButton();
    m_pSunnyPushButton->setImage("indicator", "indicator_enable_weather_mode_off.jpg");
    m_pRainyPushButton->setImage("indicator", "indicator_enable_weather_mode_on.jpg");

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->insertWidget(1, m_pSunnyPushButton, 2);
    ui->horizontalLayout2->insertWidget(2, m_pRainyPushButton ,2);

    connect(m_pSunnyPushButton, SIGNAL(clicked()), this, SLOT(on_clicked_sunny()));
    connect(m_pRainyPushButton, SIGNAL(clicked()), this, SLOT(on_clicked_rainy()));

    ui->horizontalLayout2->setStretch(6, 1);
}

void IndicatorDialog::on_cameraExposeClicked()
{
    this->hide();

    IndicatorCameraExposeWidget indicatorCameraExposeWidget;
//    m_pIndicatorCameraExposeWidget->lower();
    indicatorCameraExposeWidget.exec();
}

void IndicatorDialog::on_cameraFocusClicked()
{
    this->hide();

    IndicatorCameraFocusWidget indicatorCameraFocusWidget;
//    m_pIndicatorCameraFocusWidget->lower();
    indicatorCameraFocusWidget.exec();
}

void IndicatorDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0,0,0,128)); // 4번째 인자에 적당한 투명도를 입력합니다.
    painter.drawRect(GetWidgetSizePos(QRect(0, 125, 1600,  965)));
//    painter.setBrush(QColor(0,0,0,0)); // 4번째 인자에 적당한 투명도를 입력합니다.
//    painter.drawRect(GetWidgetSizePos(QRect(0, 0, 1600,  125)));
}

void IndicatorDialog::mousePressEvent(QMouseEvent *event)
{
    accept();
}

void IndicatorDialog::clearSecondRow()
{
    if (m_pCameraFocusPushButton != nullptr)
    {
        delete m_pCameraFocusPushButton;
        m_pCameraFocusPushButton = nullptr;
    }

    if (m_pCameraExposePushButton != nullptr)
    {
        delete m_pCameraExposePushButton;
        m_pCameraExposePushButton = nullptr;
    }

    QLayoutItem* item;
    while ( ( item = ui->horizontalLayout2->takeAt( 0 ) ) != nullptr )
    {
        QWidget* widget = item->widget();
        delete widget;
        widget = nullptr;
        delete item;
    }

    for (int i = 0 ; i < 7 ; i++)
    {
        QSpacerItem *item2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->horizontalLayout2->addItem(item2);
        ui->horizontalLayout2->setStretch(i, 2);
    }

}

void IndicatorDialog::initlize()
{
    m_jsonObject1 = m_configManager1.GetConfig();
    m_jsonObject2 = m_configManager2.GetConfig();
    m_jsonObject3 = m_configManager3.GetConfig();

    switch(m_jsonObject1["enforcement selection"].toInt())
    {
    case 1:
    {
        ui->enforcementPushButton->setImage("indicator", "indicator_mode_i.jpg");
    }
        break;
    case 2:
    {
        ui->enforcementPushButton->setImage("indicator", "indicator_mode_a.jpg");
    }
        break;
    case 3:
    {
        ui->enforcementPushButton->setImage("indicator", "indicator_mode_v.jpg");
    }
        break;
    }

    switch(m_jsonObject1["speed selection"].toInt())
    {
    case 1:
    {
        ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_on.jpg");
    }
        break;
    case 2:
    {
        ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_off.jpg");
    }
        break;
    }

    switch(m_jsonObject2["weather selection"].toInt())
    {
    case 1:
    {
        ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_off.jpg");
    }
        break;
    case 2:
    {
        ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_on.jpg");
    }
        break;
    }

    switch(m_jsonObject2["day&night selection"].toInt())
    {
    case 1:
    {
        ui->daynNightPushButton->setImage("indicator", "day1.jpg");
    }
        break;
    case 2:
    {
        ui->daynNightPushButton->setImage("indicator", "day2.jpg");
    }
        break;
    case 3:
    {
        ui->daynNightPushButton->setImage("indicator", "day3.jpg");
    }
        break;
    case 4:
    {
        ui->daynNightPushButton->setImage("indicator", "night1.jpg");
    }
        break;
    case 5:
    {
        ui->daynNightPushButton->setImage("indicator", "night2.jpg");
    }
        break;
    case 6:
    {
        ui->daynNightPushButton->setImage("indicator", "night3.jpg");
    }
        break;
    }

    ui->cameraPushButton->setImage("indicator", "camera.jpg");




    ui->comPushButton->setImage("indicator", "indicator_wifi_disconnected.jpg");
    ui->gpsPushButton->setImage("indicator", "indicator_gps_off.jpg");

    ui->screenRecordingPushButton->setImage("indicator", "screen_recording.jpg");

}

void IndicatorDialog::on_pushButton_clicked()
{
    accept();
}

void IndicatorDialog::on_screenRecordingPushButton_clicked()
{
    char buff[256];
    memset(buff, 0, 256);
    FILE* fp = popen("pidof ffmpeg", "r");
    if (fp == NULL)
    {
        perror("erro : ");
        return;
    }

    while(fgets(buff, 256, fp) != NULL)
    {
        printf("%s", buff);
    }

    if (!strlen(buff))
    {
        QString cmd;
        QString resolution = "800x480";
        QString file_name = GetSubPath("manual_capture", SD) + "/" + GetFile("SR");
        cmd = QString("ffmpeg -hwaccel opencl -y -f x11grab -framerate 10 -video_size %1 -i :0.0+0,0 -c:v libx264 -pix_fmt yuv420p -qp 0 -preset ultrafast %2 &").arg(resolution).arg(file_name);
        system(cmd.toStdString().c_str());
    }
    else
    {
        system("ps -ef | grep ffmpeg | awk '{print $2}' | xargs kill -9");
    }
}

void IndicatorDialog::on_screenCapturePushButton_clicked()
{
    QPixmap pixmap = QPixmap::grabWindow(this->winId());
    QString filename = GetSubPath("manual_capture", SD) + "/" + GetFile("SC");
    pixmap.save(filename, 0, 100);
}

void IndicatorDialog::on_day1WidgetClicked()
{    
    ui->daynNightPushButton->setImage("indicator", "day1.jpg");
    m_jsonObject2["day&night selection"] = 1;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "day1.jpg");


    QJsonObject object = m_jsonObject3["Day"].toObject()["Dark"].toObject();
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void IndicatorDialog::on_day2WidgetClicked()
{
    ui->daynNightPushButton->setImage("indicator", "day2.jpg");
    m_jsonObject2["day&night selection"] = 2;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "day2.jpg");

    QJsonObject object = m_jsonObject3["Day"].toObject()["Normal"].toObject();
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void IndicatorDialog::on_day3WidgetClicked()
{
    ui->daynNightPushButton->setImage("indicator", "day3.jpg");
    m_jsonObject2["day&night selection"] = 3;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "day3.jpg");

    QJsonObject object = m_jsonObject3["Day"].toObject()["Bright"].toObject();
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void IndicatorDialog::on_night1WidgetClicked()
{
    ui->daynNightPushButton->setImage("indicator", "night1.jpg");
    m_jsonObject2["day&night selection"] = 4;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "night1.jpg");

    QJsonObject object = m_jsonObject3["Night"].toObject()["Dark"].toObject();
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void IndicatorDialog::on_night2WidgetClicked()
{
    ui->daynNightPushButton->setImage("indicator", "night2.jpg");
    m_jsonObject2["day&night selection"] = 5;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "night2.jpg");

    QJsonObject object = m_jsonObject3["Night"].toObject()["Normal"].toObject();
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void IndicatorDialog::on_night3WidgetClicked()
{
    ui->daynNightPushButton->setImage("indicator", "night3.jpg");
    m_jsonObject2["day&night selection"] = 6;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "night3.jpg");

    QJsonObject object = m_jsonObject3["Night"].toObject()["Bright"].toObject();
    m_serialViscaManager.set_AE_shutter_priority();
    m_serialViscaManager.set_iris(object["Iris"].toInt());
    m_serialViscaManager.set_shutter_speed(object["Shutter"].toInt());
    m_serialViscaManager.set_gain(object["Gain"].toInt());
//    object["DNR"].toBool() ? m_serialViscaManager.set_noise_reduction_on(p);
    object["DIS"].toBool() ? m_serialViscaManager.set_DIS_on() : m_serialViscaManager.set_DIS_off();
    object["DEFOG"].toBool() ? m_serialViscaManager.set_defog_on() : m_serialViscaManager.set_defog_off();
    object["HLC"].toBool() ? m_serialViscaManager.set_HLC_on() : m_serialViscaManager.set_HLC_off();
}

void IndicatorDialog::on_clicked_sunny()
{
    ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_off.jpg");
    m_jsonObject2["weather selection"] = 1;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pWeatherPushbutton, "indicator", "indicator_enable_weather_mode_off.jpg");

    m_serialLaserManager.set_weather_mode(0);
}

void IndicatorDialog::on_clicked_rainy()
{
    ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_on.jpg");
    m_jsonObject2["weather selection"] = 2;
    m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pWeatherPushbutton, "indicator", "indicator_enable_weather_mode_on.jpg");

    m_serialLaserManager.set_weather_mode(1);
}
