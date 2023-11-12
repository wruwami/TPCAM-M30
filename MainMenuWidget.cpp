#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include <QTime>
#include <QFile>
#include <QSpacerItem>
#include "qdir.h"
#include <QDebug>
#include <QPainter>
#include <QFont>
#include <QFontDatabase>

#include "Color.h"
#include "IndicatorDialog.h"
#include "StringLoader.h"
#include "ConfigManager.h"
#include "WidgetSize.h"

#include "HomeButtonWidget.h"
#include "SerialGPSManager.h"
#include "FileManager.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0x000000);

    WidgetSize* ws = WidgetSize::GetInstance();

    QFile file(":/style/mainmenuWidget.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    setStyleSheet(styleSheet);

    QSizePolicy sp_retain = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sp_retain.setRetainSizeWhenHidden(true);
//    setSizePolicy(sp_retain);

//    QSizePolicy sp_retain_battery = QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
//    sp_retain_battery.setRetainSizeWhenHidden(true);
//    setSizePolicy(sp_retain);


    ui->timeLabel->setColor(Qt::white);
    //Add font
//    int fontId = QFontDatabase::addApplicationFont(GeteMMCPath()+"/font/"+"led_real.ttf");
//    int fontId = QFontDatabase::addApplicationFont(GeteMMCPath()+"/font/"+"LOOPY___.ttf");
//    int fontId = QFontDatabase::addApplicationFont(GeteMMCPath()+"/font/"+"DIGITALDREAMFAT.ttf");
    int fontId = QFontDatabase::addApplicationFont(GeteMMCPath()+"/font/"+"E1234.ttf");
    if (fontId != -1) {
        QString strled_real = QFontDatabase::applicationFontFamilies(fontId).at(0);

        // Now you can use the custom font in your application
        QFont led_real(strled_real, 28); // Replace "12" with your desired font size
        led_real.setBold(true);
        led_real.setItalic(false);
        ui->timeLabel->setFont(led_real);
    }
    ui->timeLabel->setFontSize(28);
    ui->timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter );
    ui->timeLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    ui->timeLabel->setStyleSheet(QString("QLabel { letter-spacing: -2px; line-height: 2px; letter-spacing: 0px}"));

    ui->cameraPushButton->setSizePolicy(sp_retain);
    ui->daynNightPushButton->setSizePolicy(sp_retain);
    ui->weatherPushButton->setSizePolicy(sp_retain);
    ui->enforcementPushButton->setSizePolicy(sp_retain);
    ui->speedPushButton->setSizePolicy(sp_retain);
    ui->wifiPushButton->setSizePolicy(sp_retain);
    ui->gpsPushButton->setSizePolicy(sp_retain);
    ui->batteryPercentButton->setSizePolicy(sp_retain);
    ui->batteryStatusLabel->setSizePolicy(sp_retain);
    ui->stackedWidget->setSizePolicy(sp_retain);

    ui->cameraPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));
    ui->daynNightPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));
    ui->weatherPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));
    ui->enforcementPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));
    ui->speedPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));
    ui->wifiPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));
    ui->gpsPushButton->setFixedSize(ws->GetWidgetWidth(100), ws->GetWidgetHeight(100));


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
    ui->batteryPercentButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pHomeTitleLabel = new CustomLabel;
    m_pHomeButtonWidget = new HomeButtonWidget;
    ui->stackedWidget->addWidget(m_pHomeTitleLabel);
    ui->stackedWidget->addWidget(m_pHomeButtonWidget);
    ui->stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    m_pMainMenuTitlePushButton = m_pHomeButtonWidget->m_pHomePushButton;
    m_pHomePushButton = m_pHomeButtonWidget->m_pHomePushButton;

    m_pHomeTitleLabel->setText(LoadString("IDS_MAIN_MENU"));
    m_pHomeTitleLabel->setFontSize(23);



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

    ui->batteryStatusLabel->setImage("indicator", "indicator_battery_charge_off.png");
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
        file_full_path = GeteMMCPath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery0.bmp";
    }
    else if (percent < 20 && percent > 0)
    {
        file_full_path = GeteMMCPath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery1.bmp";
    }
    else if (percent < 40 && percent >= 20)
    {
        file_full_path = GeteMMCPath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery2.bmp";
    }
    else if (percent < 60 && percent >= 40)
    {
        file_full_path = GeteMMCPath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery3.bmp";
    }
    else if (percent < 80 && percent >= 60)
    {
        file_full_path = GeteMMCPath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery4.bmp";
    }
    else if (percent >= 80)
    {
        file_full_path = GeteMMCPath() + "/" + "images" + "/" + "indicator" + "/" + "indicator_battery5.bmp";
    }

    QPixmap pixmap;
    pixmap.load(file_full_path);
//    qDebug() << pixmap.size();
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
//ui->batteryPercentButton->setFontSize(23);
}

void MainMenuWidget::setBatteryCharge(bool isCharge)
{
    if (isCharge)
        ui->batteryStatusLabel->setImage("indicator", "indicator_battery_charge_on.png");
    else
        ui->batteryStatusLabel->setImage("indicator", "indicator_battery_charge_off.png");
}

void MainMenuWidget::setIndicatorImage(CustomPushButton* pCustomButton, QString path_name, QString file_name)
{
    pCustomButton->setImage(path_name, file_name);
}

void MainMenuWidget::setTransparentBackGround(bool bTransParent)
{
    if (bTransParent)
    {
//    this->setStyleSheet("background-color: rgba(255,255,255,0;}");
//        setAttribute(Qt::WA_TranslucentBackground);
//        setStyleSheet("background-color: rgba(0,0,0,0)");
        setStyleSheet("background: transparent;");
    }
    else
    {
        setBackGroundColor(this, 0x000000);
//        setAttribute(Qt::WA_TranslucentBackground, false);
    }
}

void MainMenuWidget::hideButton()
{

    ui->cameraPushButton->hide();
    ui->daynNightPushButton->hide();
    ui->weatherPushButton->hide();
    ui->enforcementPushButton->hide();
    ui->speedPushButton->hide();
    ui->wifiPushButton->hide();
    ui->gpsPushButton->hide();

}

void MainMenuWidget::setRedLine(bool bRedLine)
{
    m_bRedLine = bRedLine;
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

void MainMenuWidget::DisableAllButton()
{
    ui->cameraPushButton->setEnabled(false);
    ui->daynNightPushButton->setEnabled(false);
    ui->weatherPushButton->setEnabled(false);
    ui->enforcementPushButton->setEnabled(false);
    ui->speedPushButton->setEnabled(false);
    ui->wifiPushButton->setEnabled(false);
    ui->gpsPushButton->setEnabled(false);
}
void MainMenuWidget::EnableAllButton()
{
    ui->cameraPushButton->setEnabled(true);
    ui->daynNightPushButton->setEnabled(true);
    ui->weatherPushButton->setEnabled(true);
    ui->enforcementPushButton->setEnabled(true);
    ui->speedPushButton->setEnabled(true);
    ui->wifiPushButton->setEnabled(true);
    ui->gpsPushButton->setEnabled(true);
}
void MainMenuWidget::setMainMenuTitle(QString title)
{
    QFile file(":/style/mainmenuWidget.qss");
    file.open(QFile::ReadOnly);

    m_pHomeTitleLabel->setStyleSheet(QString::fromLatin1(file.readAll()));
    m_pHomeTitleLabel->setText(title);
    m_pHomeTitleLabel->setFontSize(23);
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
    ui->timeLabel->setFontSize(22);
    ui->timeLabel->setColor(Qt::white);
//    if (SerialGPSManager::GetInstance()->GetSatellitesInView() >= 3)
//        ui->gpsPushButton->setImage("indicator", "indicator_gps_on.jpg");
//    else
//        ui->gpsPushButton->setImage("indicator", "indicator_gps_off.jpg");
}

void MainMenuWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (m_bRedLine)
    {
        int gap = 0;

        QPen Pen(Qt::red);
        Pen.setStyle(Qt::SolidLine);
        Pen.setWidth(10);

        painter.setPen(Pen);
//        painter.drawRect(GetWidgetSizePos(QRect(0, 0, 1600, 960)));
        painter.drawLine(gap, gap, width(), gap);
        painter.drawLine(gap, gap, gap, height());
        painter.drawLine(width() - gap, gap, width(), height());
//        painter.drawLine(gap, height() - 2 * gap, width() - 2 * gap, height() - 2 * gap);


    }
}

//void MainMenuWidget::
