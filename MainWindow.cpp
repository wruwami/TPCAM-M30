#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QDialog>

#include "CustomPushButton.h"
#include "Color.h"
#include "DateTimeWidget.h"
#include "EnforcementWidget.h"
#include "IndicatorDialog.h"
#include "MainMenuWidget.h"
#include "MainMenuContentWidget.h"
#include "MainMenuAdminAlignWidget.h"
#include "LoginWidget.h"
#include "FileManagerWidget.h"
#include "SettingWidget.h"
#include "DeviceIDWidget.h"
#include "CameraAlignWidget.h"
#include "CameraZoomFocusWidget.h"
#include "WidgetSize.h"
#include "StringLoader.h"
#include "IndicatorCameraExposeWidget.h"
#include "IndicatorCameraFocusWidget.h"
#include "SelfTestDialog.h"
#include "SerialGPSManager.h"
#include "RemoteController.h"
#include "FileManager.h"
#include "SelfTestWidget.h"
#include "BaseDialog.h"

template <typename T>
inline void removeSecondItem(T*& pointer) {
  if (pointer) {
    delete pointer;
    pointer = 0;
  }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    SelfTestDialog selfTestDialog;
//    if (selfTestDialog.exec() == QDialog::Rejected)
//        m_bLoginFail = true;
    {
        SelfTestWidget selfTestWidget;
        selfTestWidget.show();

        BaseDialog baseDialog(SelfTestWarningMessageWidgetType, selfTestWidget.m_isCamera, selfTestWidget.m_isLaser, selfTestWidget.m_isBattery, selfTestWidget.m_isStorage, Qt::AlignmentFlag::AlignCenter);
    //    baseDialog.SetSelfTestResult();
        if (baseDialog.exec() == QDialog::Rejected)
            PowerOff();

    }

    m_pMainMenuWidget = (MainMenuWidget*)ui->verticalLayout->itemAt(0)->widget();
    m_pBatteryStatus = m_pMainMenuWidget->m_pBatteryChargingLabel;
    m_pBatteryPercent = m_pMainMenuWidget->m_pBatteryPercentButton;

    m_widgetType = Login;
    m_pLoginWidget = new LoginWidget;
//    m_pMainMenuContentWidget = new MainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(m_pLoginWidget, 835);
    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_LOGIN"));
    m_pIndicatorWidget = new IndicatorDialog;
    m_pIndicatorWidget->setModal(true);
    m_pDateTimeWidget = new DateTimeWidget;
    m_pRemoteController = new RemoteController(this);
    m_pRemoteController->CreateThread();

    QSizePolicy sp_retain = ui->widget_2->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->widget->setSizePolicy(sp_retain);
    ui->widget_2->setSizePolicy(sp_retain);

    QObject::connect((QWidget*)m_pDateTimeWidget->m_pGPSCheckBox, SIGNAL(stateChanged()), this, SLOT(on_datetimeChecked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_pUserNameComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_userNameChanged(QString)));
    QObject::connect((QWidget*)m_pMainMenuWidget->m_pHomePushButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));

    CheckLoginExpired();

//    SetWarningMode();
    startTimer(1000);

    m_p100msTimer = new QTimer();
    connect(m_p100msTimer, SIGNAL(timeout()), this, SLOT(OnTimer100msFunc()));
    m_p100msTimer->start(100);
    m_p500msTimer = new QTimer();
    connect(m_p500msTimer, SIGNAL(timeout()), this, SLOT(OnTimer500msFunc()));
    m_p500msTimer->start(500);
}

MainWindow::~MainWindow()
{
//    if (m_pLoginWidget != nullptr)
//        delete m_pLoginWidget;
//    if (m_pMainMenuContentWidget != nullptr)
//        delete m_pMainMenuContentWidget;

//    if (m_pIndicatorWidget)
//    {
//        m_pIndicatorWidget->close();
//        delete m_pIndicatorWidget;
//        m_pIndicatorWidget = nullptr;
//    }

    QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
    removeSecondItem(widget);

    finalize();

    delete m_p500msTimer;
    delete m_p100msTimer;

    delete ui;
}



void MainWindow::initializeMainMenuWidget()
{
    m_pIndicatorWidget->m_bFocusExposeDisabled = true;

    m_pMainMenuWidget->show();
    if (m_userName == "admin-align")
    {
        m_widgetType = Other;
        if (ui->verticalLayout->count() > 1)
        {
            QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
            removeseconditem(widget);
        }

        ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
        if (m_pMainMenuAdminAlignWidget == nullptr)
            m_pMainMenuAdminAlignWidget = new MainMenuAdminAlignWidget;
        m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_ADMIN"));
        ui->verticalLayout->addWidget(m_pMainMenuAdminAlignWidget, 835);
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pDeviceIdWidget, SIGNAL(clicked()), this, SLOT(on_device_id_clicked()));
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pCameraAlignWidget, SIGNAL(clicked()), this, SLOT(on_camera_align_clicked()));
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pCameraZoomFocusWidget, SIGNAL(clicked()), this, SLOT(on_camera_zoom_focus()));
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pLogoButton, SIGNAL(clicked()), this, SLOT(on_logo_clicked()));
    }
    else
    {
        m_widgetType = MainMenu;

        if (ui->verticalLayout->count() > 1)
        {
            QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
            removeseconditem(widget);
        }
        ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
        if (m_pMainMenuContentWidget == nullptr)
            m_pMainMenuContentWidget = new MainMenuContentWidget;
        m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_MAIN_MENU"));
        ui->verticalLayout->addWidget(m_pMainMenuContentWidget, 835);
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pEnforcementButton, SIGNAL(clicked()), this, SLOT(on_enforcementClicked()));
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pFileManagertButton, SIGNAL(clicked()), this, SLOT(on_filemanagementClicked()));
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pSettingButton, SIGNAL(clicked()), this, SLOT(on_settingClicked()));
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pLogoButton, SIGNAL(clicked()), this, SLOT(on_logo_clicked()));

    }
}

void MainWindow::initializeLoginWidget()
{
    m_widgetType = Login;
    m_pIndicatorWidget->m_bFocusExposeDisabled = true;
    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        removeseconditem(widget);
    }
    m_userName = "admin";

//    if (m_pLoginWidget == nullptr)
        m_pLoginWidget = new LoginWidget;
//    delete m_pDateTimeWidget;
//    m_pDateTimeWidget = nullptr;

//    ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
    ui->verticalLayout->addWidget(m_pLoginWidget, 835);
    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_LOGIN"));


    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_pUserNameComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_userNameChanged(QString)));
}

void MainWindow::finalize()
{
    QLayout* layout = ui->centralWidget->layout();
//    for (int i = 0 ; ui->verticalLayout->count() ; i++)
//    {
//        QLayoutItem* item = ui->verticalLayout->itemAt(i);
//        delete item;
//    }
    QLayoutItem* item;
    while((item = ui->verticalLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    delete layout;
}

void MainWindow::open_indicator_widget()
{
    m_pIndicatorWidget->show();

//    QObject::connect((QWidget*)m_pIndicatorWidget->m_pCameraPushButton, SIGNAL(clicked()), this, SLOT(on_cameraClicked()));
}

void MainWindow::removeseconditem()
{
    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        delete widget;
        widget = nullptr;
    }
}

void MainWindow::removeseconditem(QWidget*& widget)
{
    if (ui->verticalLayout->count() > 1)
    {
        delete widget;
        widget = nullptr;
    }
}


void MainWindow::showIndicator(bool isShow)
{
    m_pMainMenuWidget->showIndicator(isShow);
}

void MainWindow::setWarningMode()
{
    m_nFailTimerId = startTimer(1000);

}

void MainWindow::SetWindowWarningMode()
{
//    setBackGroundColor(ui->centralWidget, Qt::red);
//    setWindowOpacity(0.5);
}

void MainWindow::on_cameraPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_daynNightPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_weatherPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_enforcementPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_speedPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_wifiPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_gpsPushButton_clicked()
{
    open_indicator_widget();
}

void MainWindow::on_loginWidgetClicked()
{
    if (m_userName == "admin-align")
    {
        m_widgetType = Other;
//        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
//        delete widget;
//        widget = nullptr;
        delete m_pLoginWidget;
        m_pLoginWidget = nullptr;
        ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
        if (m_pMainMenuAdminAlignWidget == nullptr)
            m_pMainMenuAdminAlignWidget = new MainMenuAdminAlignWidget;
        m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
        ui->verticalLayout->addWidget(m_pMainMenuAdminAlignWidget, 835);
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pDeviceIdWidget, SIGNAL(clicked()), this, SLOT(on_device_id_clicked()));
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pCameraAlignWidget, SIGNAL(clicked()), this, SLOT(on_camera_align_clicked()));
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pCameraZoomFocusWidget, SIGNAL(clicked()), this, SLOT(on_camera_zoom_focus()));
        QObject::connect((QWidget*)m_pMainMenuAdminAlignWidget->m_pLogoButton, SIGNAL(clicked()), this, SLOT(on_logo_clicked()));
    }
    else
    {
        m_widgetType = MainMenu;

        delete m_pLoginWidget;
        m_pLoginWidget = nullptr;
//        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
//        delete widget;
//        widget = nullptr;
        ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
//        if (m_pMainMenuContentWidget == nullptr)
            m_pMainMenuContentWidget = new MainMenuContentWidget;
        m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_MAIN_MENU"));
        ui->verticalLayout->addWidget(m_pMainMenuContentWidget, 835);
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pEnforcementButton, SIGNAL(clicked()), this, SLOT(on_enforcementClicked()));
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pFileManagertButton, SIGNAL(clicked()), this, SLOT(on_filemanagementClicked()));
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pSettingButton, SIGNAL(clicked()), this, SLOT(on_settingClicked()));
        QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pLogoButton, SIGNAL(clicked()), this, SLOT(on_logo_clicked()));
    }
}

void MainWindow::on_dateTimeWidgetClicked()
{
    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        removeseconditem(widget);
    }
//    ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
//    if (m_pLoginWidget)
//    {
//        delete m_pLoginWidget;
//        m_pLoginWidget = nullptr;
//    }
//    if (m_pDateTimeWidget == nullptr)

    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_DATE_TIME"));
    ui->verticalLayout->addWidget(m_pDateTimeWidget, 835);
    QObject::connect((QWidget*)m_pDateTimeWidget->m_pSavePushButton, SIGNAL(clicked()), this, SLOT(on_DateTimeSaveClicked()));
    QObject::connect((QWidget*)m_pDateTimeWidget->m_pCancelPushButton, SIGNAL(clicked()), this, SLOT(on_DateTimeCancelClicked()));
}

void MainWindow::on_enforcementClicked()
{
    m_widgetType = Enforcement;
    m_pIndicatorWidget->m_bFocusExposeDisabled = false;

    if (m_pMainMenuContentWidget)
    {
        delete m_pMainMenuContentWidget;
        m_pMainMenuContentWidget = nullptr;
    }
//    QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
//    delete widget;
//    widget = nullptr;

    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    if (m_pEnforcementWidget == nullptr)
        m_pEnforcementWidget = new EnforcementWidget;
    ui->verticalLayout->addWidget(m_pEnforcementWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::OpenEnforcement()
{
    if (m_widgetType == Enforcement)
        return;

    if ((m_widgetType != FileManager && m_widgetType != Setting))
        return;

    m_widgetType = Enforcement;
    m_pIndicatorWidget->m_bFocusExposeDisabled = false;
    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        if (m_pEnforcementWidget == widget)
        {
            delete m_pEnforcementWidget;
            m_pEnforcementWidget = nullptr;
        }
        else
        {
            removeseconditem(widget);
        }
    }

//    if (ui->verticalLayout->count() > 1)
//    {
//        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
//        removeseconditem(widget);
//    }

    //    if (m_pMainMenuContentWidget)
//    {
//        delete m_pMainMenuContentWidget;
//        m_pMainMenuContentWidget = nullptr;
//    }
//    if (m_pLoginWidget != nullptr)
//    {
//        delete m_pLoginWidget;
//        m_pLoginWidget = nullptr;
//    }
//    initializeMainMenuWidget();
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    if (m_pEnforcementWidget == nullptr)
        m_pEnforcementWidget = new EnforcementWidget;
    ui->verticalLayout->addWidget(m_pEnforcementWidget, 835);
    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::OpenMainMenu()
{
    if (m_widgetType != Enforcement)
        return;

    m_widgetType = MainMenu;
    showIndicator(true);

    QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
    if (m_pEnforcementWidget == widget)
    {
        delete m_pEnforcementWidget;
        m_pEnforcementWidget = nullptr;
    }
    else
    {
        removeseconditem(widget);
    }


    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }

    if (m_pMainMenuContentWidget)
    {
        delete m_pMainMenuContentWidget;
        m_pMainMenuContentWidget = nullptr;
    }

//    if (m_pCameraAlignWidget)
//    {
//        delete m_pCameraAlignWidget;
//        m_pCameraAlignWidget = nullptr;
//    }

    initializeMainMenuWidget();
}

void MainWindow::CheckBatteryPercent()
{

    //get raw values
    ltc.getValues();

    //moving average filter
    ltc.filterValues();

    //

//    if((ltc.m_filteredVolt >= 12.5) && (ltc.m_filteredCurrent >= 0.1) && (ltc.m_bACChangeFlag == true))
//    {
//        ltc.setChargeThresholdH(ltc.m_filteredAC*(0.2) + ltc.getACThresholdH()*(0.8) );
//        ltc.m_bACChangeFlag = false;
//    }
//    else if((ltc.m_filteredVolt <= 9.5) && (ltc.m_filteredCurrent <= -0.1) && (ltc.m_bACChangeFlag == false))
//    {
//        int ACDiff = ltc.m_filteredAC-5000;
//        ltc.setChargeThresholdH(ltc.getACThresholdH()-(ACDiff*0.2));
//        ltc.m_bACChangeFlag = true;
//        ltc.setRawAccumulatedCharge(5000);
//    }

//    if(ltc.m_filteredVolt <=9.4)
//    {
////        OS 자동 종료
//        QProcess::startDetached("shutdown -h now");
//    }

    // battery count
    int percent = ltc.m_filteredBat_persent/100;
    m_pMainMenuWidget->setBatteryPercentValue(percent);

}

void MainWindow::CheckBatteryCharge()
{
    //get raw values
    ltc.getValues();

    //moving average filter
    ltc.filterValues();

    int current = ltc.m_filteredCurrent;
    if (current > 0)
        m_pMainMenuWidget->setBatteryCharge(true);
    else
        m_pMainMenuWidget->setBatteryCharge(false);
}



void MainWindow::SelfTestFail(bool show)
{
    if (show)
    {
        m_redAlertWidget = new QWidget;
        m_redAlertWidget->setWindowFlags(Qt::FramelessWindowHint);
//        widget->setWindowFlags(Qt::WA_TranslucentBackground);5
        m_redAlertWidget->setGeometry(this->geometry());
//        qDebug() << this->geometry();
        m_redAlertWidget->raise();
//        widget->setStyleSheet("QLabel {background-color: rgba(255, 0, 0, 125)}");
        m_redAlertWidget->setStyleSheet("background-color: rgba(255, 0, 0, 128);");
        m_redAlertWidget->setWindowOpacity(0.4);
        m_redAlertWidget->show();
    }
    else
    {
        delete m_redAlertWidget;
        m_redAlertWidget = nullptr;
    }

}

void MainWindow::PowerOff()
{
    system("systemctl poweroff -i");
}

void MainWindow::CheckLoginExpired()
{
    ConfigManager configManager = ConfigManager("expired_date.txt");
    QString str = configManager.GetText();
    if (str.at(str.size() - 1) == '\n')
    {
        str.remove(str.size() - 1, 1);
    }
//    QFile expired_file(GetPath("", SD) + "/" + ("expired_date.txt"));
//    expired_file.open(QFile::ReadOnly);

//    if (expired_file.isOpen())
//    {
//        expired_file.copy(GetPath("", eMMC) + "/" + expired_file.Text);
//        expired_file.remove();
////        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
//    }
//    else
//    {

//    }
////    expired_file.close();

//    QByteArray ba = expired_file.readAll();
//    QString str = QString(ba);
    QDateTime datetime;
    ;
    QDateTime current_datetime;

    if (current_datetime.currentDateTime() > datetime.fromString(str, "yyyyMMdd"))
    {
        BaseDialog baseDialog(Dialog::LoginExpiredDateWidgetType, Qt::AlignmentFlag::AlignLeft, "", false, LoadString("IDS_EXPIRED_DATE"));
        baseDialog.exec();
    }

}

void MainWindow::doThirdAction()
{
    this->OpenEnforcement();
}

void MainWindow::doForthAction()
{
    ConfigManager config = ConfigManager("parameter_setting1.json");
    QJsonObject object = config.GetConfig();
    int enforcement = object["enforcement selection"].toInt();
    if (enforcement < 4 )
        enforcement++;
    else
        enforcement = 1;

    object["enforcement selection"] = enforcement;
    config.SetConfig(object);
    config.SaveFile();

}

void MainWindow::do5thAction()
{
    this->OpenFileManagement();
}

void MainWindow::doSharpAction()
{
    if (m_widgetType != Enforcement)
        return;

    m_pEnforcementWidget->m_pEnforcementComponentWidget->SaveImage();
}

void MainWindow::doStarAction()
{
    this->OpenMainMenu();
}

void MainWindow::doZeroAction()
{
    QPixmap pixmap = QPixmap::grabWindow(this->winId());
    QString filename = GetSubPath("manual_capture", SD) + "/" + GetFile("SC");
    pixmap.save(filename, 0, 100);
}

void MainWindow::do9thAction()
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

void MainWindow::OnTimer100msFunc()
{
    CheckBatteryCharge();
}

void MainWindow::OnTimer500msFunc()
{
    CheckBatteryPercent();
}


void MainWindow::on_filemanagementClicked()
{
//    m_pIndicatorWidget->setFocusExposeDisabled(t);
    m_widgetType = FileManager;

    if (m_pMainMenuContentWidget)
    {
        delete m_pMainMenuContentWidget;
        m_pMainMenuContentWidget = nullptr;
    }
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    FileManagerWidget* pFileManagerWidget = new FileManagerWidget;
    ui->verticalLayout->addWidget(new FileManagerWidget, 835);

    QObject::connect((QWidget*)pFileManagerWidget->m_pHomePushButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));
    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::OpenFileManagement()
{
    if (m_widgetType == Enforcement)
    {
        if (m_pEnforcementWidget)
        {
            delete m_pEnforcementWidget;
            m_pEnforcementWidget = nullptr;
        }
    }
    if (m_widgetType != Enforcement && m_widgetType != Setting)
        return;

    m_widgetType = FileManager;
//    if (m_pMainMenuContentWidget)
//    {
//        delete m_pMainMenuContentWidget;
//        m_pMainMenuContentWidget = nullptr;
//    }

    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        removeseconditem(widget);

        ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    }

    ui->verticalLayout->addWidget(new FileManagerWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");

}

void MainWindow::on_settingClicked()
{
    m_widgetType = Setting;
//    m_pIndicatorWidget->setFocusExposeDisabled(false);

    if (m_pMainMenuContentWidget)
    {
        delete m_pMainMenuContentWidget;
        m_pMainMenuContentWidget = nullptr;
    }

    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    SettingWidget* pSettingWidget = new SettingWidget;
    ui->verticalLayout->addWidget(pSettingWidget, 835);

    QObject::connect((QWidget*)pSettingWidget->m_pSavePushButton, SIGNAL(clicked()), this, SLOT(on_SettingSaveClicked()));
    QObject::connect((QWidget*)pSettingWidget->m_pCancelPushButton, SIGNAL(clicked()), this, SLOT(on_SettingCancelClicked()));


    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_SETTING"));
}

//void MainWindow::on_mainMenuTitlePushButton_clicked()
//{
//    initializeMainMenuWidget();
//}

void MainWindow::on_device_id_clicked()
{
    delete m_pMainMenuAdminAlignWidget;
    m_pMainMenuAdminAlignWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    DeviceIDWidget* pDeviceIDWidget = new DeviceIDWidget;
    ui->verticalLayout->addWidget(pDeviceIDWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
    QObject::connect((QWidget*)pDeviceIDWidget->m_pSaveButton, SIGNAL(clicked()), this, SLOT(on_DeviceIdSaveClicked()));
    QObject::connect((QWidget*)pDeviceIDWidget->m_pCancelButton, SIGNAL(clicked()), this, SLOT(on_DeviceIdCancelClicked()));
}

void MainWindow::on_camera_align_clicked()
{
    m_pMainMenuWidget->hide();
    delete m_pMainMenuAdminAlignWidget;
    m_pMainMenuAdminAlignWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    if (m_pCameraAlignWidget == nullptr)
        m_pCameraAlignWidget = new CameraAlignWidget;
    ui->verticalLayout->addWidget(m_pCameraAlignWidget, 960);
    QObject::connect((QWidget*)m_pCameraAlignWidget->m_pHomeButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));

}

void MainWindow::on_camera_zoom_focus()
{
    delete m_pMainMenuAdminAlignWidget;
    m_pMainMenuAdminAlignWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new CameraZoomFocusWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");

    showIndicator(false);
}

void MainWindow::on_SettingSaveClicked()
{
    initializeMainMenuWidget();
}

void MainWindow::on_SettingCancelClicked()
{
    initializeMainMenuWidget();
}

void MainWindow::on_DateTimeSaveClicked()
{
    initializeLoginWidget();
}

void MainWindow::on_DateTimeCancelClicked()
{
    initializeLoginWidget();
}

void MainWindow::on_mainMenuHomeClicked()
{
    showIndicator(true);

    QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
    if (m_pEnforcementWidget == widget)
    {
        delete m_pEnforcementWidget;
        m_pEnforcementWidget = nullptr;
    }
    else
    {
        removeseconditem(widget);
    }


    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }

    if (m_pMainMenuContentWidget)
    {
        delete m_pMainMenuContentWidget;
        m_pMainMenuContentWidget = nullptr;
    }

//    if (m_pCameraAlignWidget)
//    {
//        delete m_pCameraAlignWidget;
//        m_pCameraAlignWidget = nullptr;
//    }

    initializeMainMenuWidget();
}

void MainWindow::on_logo_clicked()
{

    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }

    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }

    initializeLoginWidget();
}

void MainWindow::on_userNameChanged(QString arg)
{
    m_userName = arg;
}

void MainWindow::on_DeviceIdSaveClicked()
{
    on_mainMenuHomeClicked();
}

void MainWindow::on_DeviceIdCancelClicked()
{
    on_mainMenuHomeClicked();
}

void MainWindow::on_datetimeChecked()
{
    if (SerialGPSManager::GetInstance()->GetSatellitesInView() != 0)
        m_pDateTimeWidget->SetGPSUTCDateTime(SerialGPSManager::GetInstance()->GetDateTime());
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    SetWindowWarningMode();

//    CheckBatteryPercent();

//    if (m_bLoginFail)
//    {
//        m_bFlick = !m_bFlick;
//        SelfTestFail(m_bFlick);
//    }


}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
//    QPainter painter(this);
    //    painter.fillRect(rect(), QBrush(QColor(255, 0, 0, 128)));
}

void MainWindow::doFirstAction()
{
    if (m_widgetType != Enforcement)
        return;

    m_pEnforcementWidget->m_pEnforcementComponentWidget->dzPlus();

}

void MainWindow::doSecondAction()
{
    if (m_widgetType != Enforcement)
        return;

    m_pEnforcementWidget->m_pEnforcementComponentWidget->dzMinus();
}

