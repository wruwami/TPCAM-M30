#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include <QTime>
#include <QFile>
#include <QSpacerItem>
#include "qdir.h"
#include <QDebug>

#include "Color.h"
#include "IndicatorDialog.h"
#include "StringLoader.h"
#include "ConfigManager.h"

#include "HomeButtonWidget.h"
#include "SerialGPSManager.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0x000000);

    QFile file(":/style/mainmenuWidget.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    setStyleSheet(styleSheet);

    QSizePolicy sp_retain = sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    setSizePolicy(sp_retain);

    m_pCameraPushbutton = ui->cameraPushButton;
    m_pDaynNightPushbutton = ui->daynNightPushButton;
    m_pWeatherPushbutton = ui->weatherPushButton;
    m_pEnforcementPushbutton = ui->enforcementPushButton;
    m_pSpeedPushbutton = ui->speedPushButton;
    m_pWifiPushbutton = ui->wifiPushButton;
    m_pGpsPushbutton = ui->gpsPushButton;
    m_pBatteryChargingLabel = ui->batteryStatusLabel;
    m_pBatteryPercentButton= ui->batteryPercentButton;

    ui->batteryPercentButton->setStyleSheet("QToolButton {color:#FFFF00;}");

    m_pHomeTitleLabel = new CustomLabel;
    m_pHomeButtonWidget = new HomeButtonWidget;
    ui->stackedWidget->addWidget(m_pHomeTitleLabel);
    ui->stackedWidget->addWidget(m_pHomeButtonWidget);
    m_pSpacerItem = new QSpacerItem(m_pCameraPushbutton->width(), m_pCameraPushbutton->height(), QSizePolicy::Expanding, QSizePolicy::Expanding);


//    m_pMainMenuTitlePushButton = m_pHomeButtonWidget->m_pHomePushButton;
    m_pHomePushButton = m_pHomeButtonWidget->m_pHomePushButton;

    m_pHomeTitleLabel->setText("Main Menu");



#if 0
    ui->daynNightPushButton->setImage("indicator", "indicator_enable_night_mode_off.bmp", ui->daynNightPushButton->size());
    ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_on.bmp", ui->weatherPushButton->size());
    ui->enforcementPushButton->setImage("indicator", "indicator_mode_v.bmp");
    ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_on.bmp", ui->speedPushButton->size());
    ui->wifiPushButton->setImage("indicator", "indicator_wifi_disconnected.bmp", ui->wifiPushButton->size());
    ui->gpsPushButton->setImage("indicator", "indicator_gps_off.bmp", ui->gpsPushButton->size());

    ui->batteryPercentLabel->setImage("indicator", "indicator_battery4.bmp", ui->batteryPercentLabel->size());
    ui->batteryStatusLabel->setImage("indicator", "charging.png", ui->batteryStatusLabel->size());
#else
#endif

    initImage();

    ui->batteryStatusLabel->setImage("indicator", "indicator_battery_charge_off.bmp");
    startTimer(1000);
}

MainMenuWidget::~MainMenuWidget()
{
//    delete m_pSpacerItem;
    delete m_pHomeTitleLabel;
    delete m_pHomeButtonWidget;
    delete ui;
}

void MainMenuWidget::showIndicator(bool isShow)
{
    if (isShow)
    {
//        for (int i = 1 ; i < 8 ; i++)
        {
            ui->horizontalLayout_2->removeItem(m_pSpacerItem);
        }
        ui->cameraPushButton->show();
        ui->daynNightPushButton->show();
        ui->weatherPushButton->show();
        ui->enforcementPushButton->show();
        ui->speedPushButton->show();
        ui->wifiPushButton->show();
        ui->gpsPushButton->show();

    }
    else
    {
        for (int i = 1 ; i < 8 ; i++)
        {
            ui->horizontalLayout_2->insertItem(i, m_pSpacerItem);
        }

        ui->cameraPushButton->hide();
        ui->daynNightPushButton->hide();
        ui->weatherPushButton->hide();
        ui->enforcementPushButton->hide();
        ui->speedPushButton->hide();
        ui->wifiPushButton->hide();
        ui->gpsPushButton->hide();

    }
}

void MainMenuWidget::setBatteryPercentValue(int percent)
{
    QDir qdir;
    QString file_full_path;

    if (percent == 0)
    {
        file_full_path = qdir.absolutePath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery0.bmp";
    }
    else if (percent < 20 && percent > 0)
    {
        file_full_path = qdir.absolutePath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery1.bmp";
    }
    else if (percent < 40 && percent >= 20)
    {
        file_full_path = qdir.absolutePath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery2.bmp";
    }
    else if (percent < 60 && percent >= 40)
    {
        file_full_path = qdir.absolutePath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery3.bmp";
    }
    else if (percent < 80 && percent >= 60)
    {
        file_full_path = qdir.absolutePath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery4.bmp";
    }
    else if (percent >= 80)
    {
        file_full_path = qdir.absolutePath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery5.bmp";
    }

    QPixmap pixmap;
    pixmap.load(file_full_path);
    qDebug() << pixmap.size();
    //    QUrl url(file_full_path);
    //    url.set
    //
        ui->batteryPercentButton->setStyleSheet(QString("QToolButton { \
                                    background-color: black; \
                                    border-image: url(%0);\
                                    color: #FFFF00;\
                                }\
                                ").arg(file_full_path));

    ui->batteryPercentButton->setText(QString("%0%").arg(percent));
}

void MainMenuWidget::setBatteryCharge(bool isCharge)
{
    if (isCharge)
        ui->batteryStatusLabel->setImage("indicator", "indicator_battery_charge_on.bmp");
    else
        ui->batteryStatusLabel->setImage("indicator", "indicator_battery_charge_off.bmp");
}

void MainMenuWidget::setIndicatorImage(CustomPushButton* pCustomButton, QString path_name, QString file_name)
{
    pCustomButton->setImage(path_name, file_name);
}

void MainMenuWidget::initImage()
{
    ConfigManager config1 = ConfigManager("parameter_setting1.json");
    ConfigManager config2 = ConfigManager("parameter_setting2.json");
    QJsonObject object1 = config1.GetConfig();
    QJsonObject object2 = config2.GetConfig();

    ui->cameraPushButton->setImage("indicator", "camera.jpg");
//    ui->daynNightPushButton->setImage("indicator", "indicator_enable_night_mode_off.jpg");
//    ui->weatherPushButton->setImage("indicator", "indicator_enable_weather_mode_on.jpg");
//    ui->speedPushButton->setImage("indicator", "indicator_enable_user_mode_on.jpg");
    ui->wifiPushButton->setImage("indicator", "indicator_wifi_disconnected.jpg");
    ui->gpsPushButton->setImage("indicator", "indicator_gps_off.jpg");

        switch(object1["enforcement selection"].toInt())
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

        switch(object1["speed selection"].toInt())
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

        switch(object2["weather selection"].toInt())
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

        switch(object2["day&night selection"].toInt())
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
}


void MainMenuWidget::setMainMenuTitle(QString title)
{
    QFile file(":/style/mainmenuWidget.qss");
    file.open(QFile::ReadOnly);

    m_pHomeTitleLabel->setStyleSheet(QString::fromLatin1(file.readAll()));
    m_pHomeTitleLabel->setText(title);
    ui->stackedWidget->setCurrentIndex(0);

//    m_pHomeTitleLabel->
//    ui->mainMenuTitlePushButton->setDisabled(true);
}

void MainMenuWidget::setMainMenuImage(QString path_name, QString file_name)
{
//    m_pHomeButtonWidget->m_pHomePushButton->setImage(path_name, file_name);
    ui->stackedWidget->setCurrentIndex(1);

//    ui->mainMenuTitlePushButton->setDisabled(false);
}


void MainMenuWidget::enableButtons(bool enable)
{
    ui->cameraPushButton->setEnabled(enable);
    ui->daynNightPushButton->setEnabled(enable);
    ui->weatherPushButton->setEnabled(enable);
    ui->enforcementPushButton->setEnabled(enable);
    ui->speedPushButton->setEnabled(enable);
    ui->wifiPushButton->setEnabled(enable);
    ui->gpsPushButton->setEnabled(enable);
}

void MainMenuWidget::updateStretch()
{
    ui->horizontalLayout_2->setStretch(0, 442);
    ui->horizontalLayout_2->setStretch(1, 87);
    ui->horizontalLayout_2->setStretch(2, 87);
    ui->horizontalLayout_2->setStretch(3, 87);
    ui->horizontalLayout_2->setStretch(4, 87);
    ui->horizontalLayout_2->setStretch(5, 87);
    ui->horizontalLayout_2->setStretch(6, 87);
    ui->horizontalLayout_2->setStretch(7, 87);
    ui->horizontalLayout_2->setStretch(8, 148);
    ui->horizontalLayout_2->setStretch(9, 27);
    ui->horizontalLayout_2->setStretch(10, 374);
}

void MainMenuWidget::timerEvent(QTimerEvent *event)
{
    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm:ss"));
    if (SerialGPSManager::GetInstance()->GetSatellitesInView() > 0)
        ui->gpsPushButton->setImage("indicator", "indicator_gps_on.jpg");
    else
        ui->gpsPushButton->setImage("indicator", "indicator_gps_off.jpg");
}


//void MainMenuWidget::on_cameraPushButton_clicked()
//{

//}

//void MainMenuWidget::on_daynNightPushButton_clicked()
//{

//}

//void MainMenuWidget::on_weatherPushButton_clicked()
//{

//}

//void MainMenuWidget::on_enforcementPushButton_clicked()
//{

//}

//void MainMenuWidget::on_speedPushButton_clicked()
//{

//}

//void MainMenuWidget::on_wifiPushButton_clicked()
//{

//}

//void MainMenuWidget::on_gpsPushButton_clicked()
//{

//}


