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
#include "ScreenSaver.h"
#include "camera.h"
#include "CustomComboBox.h"
#include "SerialLaserManager.h"
#include "EnforcementComponentWidget.h"

template <typename T>
inline void removeSecondItem(T*& pointer) {
  if (pointer) {
    delete pointer;
    pointer = 0;
  }
}

int g_nCrackDownIndex = 1;
SerialLaserManager* g_pSerialLaserManager = nullptr;
SerialViscaManager* g_pSerialViscaManager = nullptr;

MainWindow::MainWindow(screensaver* screensaver, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    SelfTestDialog selfTestDialog;
//    if (selfTestDialog.exec() == QDialog::Rejected)
//        m_bLoginFail = true;
    {
        QEventLoop loop;
        SelfTestWidget selfTestWidget;
        selfTestWidget.show();
        connect(&selfTestWidget, SIGNAL(selftest_finished()), &loop, SLOT(quit()));
        loop.exec();

        if (selfTestWidget.m_nCamera == Check)
            selfTestWidget.m_nCamera = Fail;
        if (selfTestWidget.m_nLaser == Check)
            selfTestWidget.m_nLaser = Fail;

        if (!(selfTestWidget.m_nCamera == Pass && selfTestWidget.m_nLaser == Pass && selfTestWidget.m_nStorage == Pass && selfTestWidget.m_nBattery == Pass))
        {
            BaseDialog baseDialog(SelfTestWarningMessageWidgetType, selfTestWidget.m_nCamera, selfTestWidget.m_nLaser, selfTestWidget.m_nBattery, selfTestWidget.m_nStorage, Qt::AlignmentFlag::AlignCenter);
            if (baseDialog.exec() == QDialog::Rejected)
                PowerOff();
            m_bSelfTestFailed = true;
        }
    }
    ui->verticalLayout->setSpacing(0);
    SetMainWindowRect(centralWidget()->rect());
    m_pMainMenuWidget = (MainMenuWidget*)ui->verticalLayout->itemAt(0)->widget();
    m_pBatteryStatus = m_pMainMenuWidget->m_pBatteryChargingLabel;
    m_pBatteryPercent = m_pMainMenuWidget->m_pBatteryPercentButton;

    m_widgetType = Login;
    m_pLoginWidget = new LoginWidget;
    m_userName = m_pLoginWidget->m_pUserNameComboBox->currentText();
//    m_pMainMenuContentWidget = new MainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(m_pLoginWidget, 835);
    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_LOGIN"));
    m_pIndicatorWidget = new IndicatorDialog;
    m_pIndicatorWidget->setModal(true);
    m_pIndicatorWidget->SetMainMenu(m_pMainMenuWidget);
    m_pDateTimeWidget = new DateTimeWidget;
    m_pRemoteController = new RemoteController(this);
    m_pRemoteController->CreateThread();
    m_pSerialLaserManager = new SerialLaserManager;
    m_pSerialViscaManager = new SerialViscaManager;
    g_pSerialLaserManager = m_pSerialLaserManager;
    g_pSerialViscaManager = m_pSerialViscaManager;

    QSizePolicy sp_retain = ui->widget_2->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->widget->setSizePolicy(sp_retain);
    ui->widget_2->setSizePolicy(sp_retain);

    QObject::connect((QWidget*)m_pDateTimeWidget->m_pGPSCheckBox, SIGNAL(stateChanged()), this, SLOT(on_datetimeChecked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_pUserNameComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_userNameChanged(QString)));
    QObject::connect((QWidget*)m_pMainMenuWidget->m_pHomePushButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));

//    BatteryInit();
//    device use

    get(screensaver);


//    SetWarningMode();
    startTimer(1000);

    CheckPowerSavingTime();

    m_p100msTimer = new QTimer();
    connect(m_p100msTimer, SIGNAL(timeout()), this, SLOT(OnTimer100msFunc()));
    m_p100msTimer->start(100);
    m_p500msTimer = new QTimer();
    connect(m_p500msTimer, SIGNAL(timeout()), this, SLOT(OnTimer500msFunc()));
    m_p500msTimer->start(500);
}

MainWindow::~MainWindow()
{
    if (m_pSerialLaserManager)
    {
        delete m_pSerialLaserManager;
        m_pSerialLaserManager = nullptr;
    }

    if (m_pSerialViscaManager)
    {
        delete m_pSerialViscaManager;
        m_pSerialViscaManager = nullptr;
    }


    delete m_screensaver;
//    if (m_pLoginWidget != nullptr)
//        delete m_pLoginWidget;
//    if (m_pMainMenuContentWidget != nullptr)
//        delete m_pMainMenuContentWidget;

//    if (m_pIndicatorWidget)+
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
    m_pMainMenuWidget->show();

    if (m_pCamera != nullptr)
    {
        delete m_pCamera;
        m_pCamera = nullptr;
    }

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
        m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
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
    m_pIndicatorWidget->setFocusExposeDisabled(true);
    m_pIndicatorWidget->m_bFocusExposeDisabled = true;

    m_pIndicatorWidget->m_bEnforcement = false;

    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        if (m_pDateTimeWidget == widget)
        {
            delete m_pDateTimeWidget;
            m_pDateTimeWidget = nullptr;
        }
        else
        {
            removeseconditem(widget);
        }

    }


//    if (m_pLoginWidget == nullptr)
        m_pLoginWidget = new LoginWidget;
//    delete m_pDateTimeWidget;
//    m_pDateTimeWidget = nullptr;
    m_userName = m_pLoginWidget->m_pUserNameComboBox->currentText();
//    ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
    ui->verticalLayout->addWidget(m_pLoginWidget, 835);
    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_LOGIN"));


    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_pUserNameComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_userNameChanged(QString)));
//    disconnect(m_pIndicatorWidget->m_pIndicatorCameraFocusWidget->m_pAutoTriggerPushButton, SIGNAL(clicked()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_readyPushButton_clicked()));
//    disconnect(m_pEnforcementWidget->m_pEnforcementComponentWidget->m_pReadyButton, SIGNAL(clicked()), m_pIndicatorWidget->m_pIndicatorCameraFocusWidget, SLOT(on_autoTriggerPushButton_clicked()));
//    disconnect(m_pIndicatorWidget, SIGNAL(sig_Night()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_Night()));
//    disconnect(m_pIndicatorWidget, SIGNAL(sig_STMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_STMode()));
//    disconnect(m_pIndicatorWidget, SIGNAL(sig_LTMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_LTMode()));
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
    m_pIndicatorWidget->setFocusExposeDisabled(true);
    m_pIndicatorWidget->m_bFocusExposeDisabled = true;
    m_pIndicatorWidget->m_bEnforcement = false;
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
//    disconnect(m_pIndicatorWidget->m_pIndicatorCameraFocusWidget->m_pAutoTriggerPushButton, SIGNAL(clicked()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_readyPushButton_clicked()));
//    disconnect(m_pEnforcementWidget->m_pEnforcementComponentWidget->m_pReadyButton, SIGNAL(clicked()), m_pIndicatorWidget->m_pIndicatorCameraFocusWidget, SLOT(on_autoTriggerPushButton_clicked()));
//    disconnect(m_pIndicatorWidget, SIGNAL(sig_Night()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_Night()));
//    disconnect(m_pIndicatorWidget, SIGNAL(sig_STMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_STMode()));
//    disconnect(m_pIndicatorWidget, SIGNAL(sig_LTMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_LTMode()));
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
    if (m_pDateTimeWidget == nullptr)
        m_pDateTimeWidget = new DateTimeWidget;
    ui->verticalLayout->addWidget(m_pDateTimeWidget, 835);
    QObject::connect((QWidget*)m_pDateTimeWidget->m_pSavePushButton, SIGNAL(clicked()), this, SLOT(on_DateTimeSaveClicked()));
    QObject::connect((QWidget*)m_pDateTimeWidget->m_pCancelPushButton, SIGNAL(clicked()), this, SLOT(on_DateTimeCancelClicked()));
}

void MainWindow::on_enforcementClicked()
{
    m_widgetType = Enforcement;
    m_pIndicatorWidget->setFocusExposeDisabled(false);
    m_pIndicatorWidget->m_bFocusExposeDisabled = false;
    m_pIndicatorWidget->m_bEnforcement = true;


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
    m_pMainMenuWidget->setTransparentBackGround(true);
    m_pEnforcementWidget->m_pEnforcementComponentWidget->setPSerialLaserManager(m_pSerialLaserManager);
    m_pIndicatorWidget->setPSerialLaserManager(m_pSerialLaserManager);
    m_pEnforcementWidget->m_pEnforcementComponentWidget->setPSerialViscaManager(m_pSerialViscaManager);
    m_pIndicatorWidget->setPSerialViscaManager(m_pSerialViscaManager);


    m_pEnforcementWidget->m_pEnforcementComponentWidget->laserInit();
    m_pEnforcementWidget->m_pEnforcementComponentWidget->camInit();
//    connect(m_pIndicatorWidget->m_pIndicatorCameraFocusWidget->m_pAutoTriggerPushButton, SIGNAL(clicked()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_readyPushButton_clicked()));
//    connect(m_pEnforcementWidget->m_pEnforcementComponentWidget->m_pReadyButton, SIGNAL(clicked()), m_pIndicatorWidget->m_pIndicatorCameraFocusWidget, SLOT(on_autoTriggerPushButton_clicked()));
    connect(m_pIndicatorWidget, SIGNAL(sig_Night()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_Night()));
    connect(m_pIndicatorWidget, SIGNAL(sig_STMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_STMode()));
    connect(m_pIndicatorWidget, SIGNAL(sig_LTMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_LTMode()));
    connect(m_pIndicatorWidget, SIGNAL(sig_EnforcementModeI()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_EnforceModeI()));
    connect(m_pIndicatorWidget, SIGNAL(sig_EnforcementModeA()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_EnforceModeA()));
    connect(m_pIndicatorWidget, SIGNAL(sig_EnforcementModeV()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_EnforceModeV()));
    connect(m_pEnforcementWidget->m_pEnforcementComponentWidget, SIGNAL(ShowRedOutLine(bool)), this, SLOT(on_ShowRedOutLine(bool)));
    connect(m_pEnforcementWidget->m_pEnforcementComponentWidget, SIGNAL(sig_exit()), this, SLOT(on_mainMenuHomeClicked()));
    if (m_userName == "admin-test")
        m_pEnforcementWidget->m_pEnforcementComponentWidget->m_bVirtualMode = true;
    else
        m_pEnforcementWidget->m_pEnforcementComponentWidget->m_bVirtualMode = false;
    SetCamera();
    m_pEnforcementWidget->m_pEnforcementComponentWidget->SetCamera(m_pCamera);
}

void MainWindow::OpenEnforcement()
{
    if (m_widgetType == Enforcement)
        return;

    if (m_widgetType != FileManager && m_widgetType != Setting && m_widgetType != MainMenu)
        return;

    m_widgetType = Enforcement;
    m_pIndicatorWidget->setFocusExposeDisabled(false);
    m_pIndicatorWidget->m_bFocusExposeDisabled = false;
    m_pIndicatorWidget->m_bEnforcement = true;
    if (ui->verticalLayout->count() > 1)
    {
        QWidget* widget = ui->verticalLayout->itemAt(1)->widget();
        if (m_pEnforcementWidget == widget)
        {
            delete m_pEnforcementWidget;
            m_pEnforcementWidget = nullptr;
        }
        else if (m_pMainMenuContentWidget == widget)
        {
            delete m_pMainMenuContentWidget;
            m_pMainMenuContentWidget = nullptr;
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
    m_pMainMenuWidget->setTransparentBackGround(true);
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    if (m_pEnforcementWidget == nullptr)
        m_pEnforcementWidget = new EnforcementWidget;
    ui->verticalLayout->addWidget(m_pEnforcementWidget, 835);
    m_pEnforcementWidget->m_pEnforcementComponentWidget->setPSerialLaserManager(m_pSerialLaserManager);
    m_pIndicatorWidget->setPSerialLaserManager(m_pSerialLaserManager);
    m_pEnforcementWidget->m_pEnforcementComponentWidget->setPSerialViscaManager(m_pSerialViscaManager);
    m_pIndicatorWidget->setPSerialViscaManager(m_pSerialViscaManager);


    m_pEnforcementWidget->m_pEnforcementComponentWidget->laserInit();
    m_pEnforcementWidget->m_pEnforcementComponentWidget->camInit();
//    connect(m_pIndicatorWidget->m_pIndicatorCameraFocusWidget->m_pAutoTriggerPushButton, SIGNAL(clicked()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_readyPushButton_clicked()));
//    connect(m_pEnforcementWidget->m_pEnforcementComponentWidget->m_pReadyButton, SIGNAL(clicked()), m_pIndicatorWidget->m_pIndicatorCameraFocusWidget, SLOT(on_autoTriggerPushButton_clicked()));
    connect(m_pIndicatorWidget, SIGNAL(sig_Night()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_Night()));
    connect(m_pIndicatorWidget, SIGNAL(sig_STMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_STMode()));
    connect(m_pIndicatorWidget, SIGNAL(sig_LTMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_LTMode()));
    connect(m_pIndicatorWidget, SIGNAL(sig_E`nforcementModeI()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_EnforceModeI()));
    connect(m_pIndicatorWidget, SIGNAL(sig_EnforcementModeA()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_EnforceModeA()));
    connect(m_pIndicatorWidget, SIGNAL(sig_EnforcementModeV()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_EnforceModeV()));
    connect(m_pEnforcementWidget->m_pEnforcementComponentWidget, SIGNAL(ShowRedOutLine(bool)), this, SLOT(on_ShowRedOutLine(bool)));
    connect(m_pEnforcementWidget->m_pEnforcementComponentWidget, SIGNAL(sig_exit()), this, SLOT(on_mainMenuHomeClicked()));

//    disconnect(m_pIndicatorWidget, SIGNAL(sig_LTMode()), m_pEnforcementWidget->m_pEnforcementComponentWidget, SLOT(on_LTMode()));
    if (m_userName == "admin-test")
        m_pEnforcementWidget->m_pEnforcementComponentWidget->m_bVirtualMode = true;
    else
        m_pEnforcementWidget->m_pEnforcementComponentWidget->m_bVirtualMode = false;

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
    SetCamera();
    m_pEnforcementWidget->m_pEnforcementComponentWidget->SetCamera(m_pCamera);
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
    // load setting_battery.json
    ConfigManager config = ConfigManager("setting_battery.json");
    QJsonObject object = config.GetConfig();

    static double dPowerOffVoltage = object["PowerOffVoltage"].toDouble();
    static double dVoltageThreasholdMax = object["VoltageThreasholdMax"].toDouble();
    static double dVoltageThreasholdMin = object["VoltageThreasholdMin"].toDouble();
    static int nChargeThreasholdMin = object["ChargeThreasholdMin"].toInt();
    static double dIsChargingAmpere = object["IsChargingAmpere"].toDouble();

    //get raw values
    ltc.getValues();

    //moving average filter
    ltc.filterValues();

    //

    if((ltc.m_filteredVolt >= dVoltageThreasholdMax) && (ltc.m_filteredCurrent >= 0.1) && (ltc.m_bACChangeFlag == true))
    {
        ltc.setChargeThresholdH(ltc.m_filteredAC*(0.2) + ltc.getACThresholdH()*(0.8) );
        ltc.m_bACChangeFlag = false;
    }
    else if((ltc.m_filteredVolt <= dVoltageThreasholdMin) && (ltc.m_filteredCurrent <= -0.1) && (ltc.m_bACChangeFlag == false))
    {
        int ACDiff = ltc.m_filteredAC-nChargeThreasholdMin;
        ltc.setChargeThresholdH(ltc.getACThresholdH()-(ACDiff*0.2));
        ltc.m_bACChangeFlag = true;
        ltc.setRawAccumulatedCharge(nChargeThreasholdMin);
    }

    if(ltc.m_filteredVolt <dPowerOffVoltage)
    {
//        OS 자동 종료
        QProcess::startDetached("shutdown -h now");
    }

    // battery count
    int percent = ltc.m_filteredBat_persent/100;
    m_pMainMenuWidget->setBatteryPercentValue(percent);

}

void MainWindow::CheckBatteryCharge()
{
    // load setting_battery.json
    ConfigManager config = ConfigManager("setting_battery.json");
    QJsonObject object = config.GetConfig();

    static double dPowerOffVoltage = object["PowerOffVoltage"].toDouble();
    static double dVoltageThreasholdMax = object["VoltageThreasholdMax"].toDouble();
    static double dVoltageThreasholdMin = object["VoltageThreasholdMin"].toDouble();
    static int nChargeThreasholdMin = object["ChargeThreasholdMin"].toInt();
    static double dIsChargingAmpere = object["IsChargingAmpere"].toDouble();
    //get raw values
    ltc.getValues();

    //moving average filter
    ltc.filterValues();

    //

    if((ltc.m_filteredVolt >= dVoltageThreasholdMax) && (ltc.m_filteredCurrent >= 0.1) && (ltc.m_bACChangeFlag == true))
    {
        ltc.setChargeThresholdH(ltc.m_filteredAC*(0.2) + ltc.getACThresholdH()*(0.8) );
        ltc.m_bACChangeFlag = false;
    }
    else if((ltc.m_filteredVolt <= dVoltageThreasholdMin) && (ltc.m_filteredCurrent <= -0.1) && (ltc.m_bACChangeFlag == false))
    {
        int ACDiff = ltc.m_filteredAC-nChargeThreasholdMin;
        ltc.setChargeThresholdH(ltc.getACThresholdH()-(ACDiff*0.2));
        ltc.m_bACChangeFlag = true;
        ltc.setRawAccumulatedCharge(nChargeThreasholdMin);
    }

    double current = ltc.m_filteredCurrent;
    if (current >= dIsChargingAmpere)
        m_pMainMenuWidget->setBatteryCharge(true);
    else
        m_pMainMenuWidget->setBatteryCharge(false);
}



void MainWindow::SelfTestFail(bool show)
{
    if (show)
    {
        m_redAlertWidget = new QWidget(this);
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
        if (m_redAlertWidget != nullptr)
        {
            delete m_redAlertWidget;
            m_redAlertWidget = nullptr;
        }
    }

}

void MainWindow::PowerOff()
{
    system("systemctl poweroff -i");
}

void MainWindow::CheckLoginExpired()
{
//    ConfigManager configManager = ConfigManager("expired_date.txt");
//    QString str = configManager.GetText();
    QString str;
    QFile expired_file(GetPath("/settings", eMMC) + "/" + ("expired_date.txt"));
    expired_file.open(QFile::ReadOnly);
    if (!expired_file.isOpen())
    {
        qDebug() << "no file has been opened";
//        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
    }
    else
    {
        QByteArray ba = expired_file.readAll();
        QString str = QString(ba);
        str.replace(" ", "");
    }
    expired_file.close();

    if (str.isEmpty())
        return;

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

    QDateTime current_datetime;

    qDebug() << current_datetime.currentDateTime();
    qDebug() << datetime.fromString(str, "yyyyMMdd");

    if (current_datetime.currentDateTime() > datetime.fromString(str, "yyyyMMdd"))
    {
        BaseDialog baseDialog(Dialog::LoginExpiredDateWidgetType, Qt::AlignmentFlag::AlignLeft, "", false, LoadString("IDS_EXPIRED_DATE"));
        baseDialog.setModal(true);
        baseDialog.exec();
    }

}

void MainWindow::CheckPowerSavingTime()
{
    // power saveing time
    ConfigManager config = ConfigManager("parameter_setting7.json");
    QJsonObject object = config.GetConfig();
    switch (object["power saving select"].toInt())
    {
    case 1:
    {
        m_nPowerSavingMinute = 0;
    }
        break;
    case 2:
    {
        m_nPowerSavingMinute = 10;
    }
        break;
    case 3:
    {
        m_nPowerSavingMinute = 20;
    }
        break;
    case 4:
    {
        m_nPowerSavingMinute = 30;
    }
        break;
    }

    if (m_nPowerSavingMinute)
    {
        m_screensaver->Setstart(true);
        m_screensaver->settime(m_nPowerSavingMinute);
        m_screensaver->timestart();
    }
    else
    {
        m_screensaver->Setstart(false);
        m_screensaver->timestop();
    }

//    if (m_nCheckSecond == 10 && m_nPowerSavingSecond != 0)
//    {
//        SetPowerSavingMode(true);
//        m_bPowerSavingMode = true;
//        m_nCheckSecond = 0;
////        m_nPowerOffSecond++;
////        if ()
//        qDebug() << "power save on" << sec;
//    }
//    if (m_bPowerSavingMode)
//    {
//        m_nPowerOffSecond++;
//        if (m_nPowerOffSecond == 10)
//            qDebug() << "poweroff" << sec;
////            system("systemctl poweroff -i");
//    }
//    else
//    {
//        m_nPowerOffSecond = 0;
//    }
//    m_nCheckSecond++;
}

void MainWindow::SetPowerSavingMode(bool bSet)
{
    if (bSet)
    {
        system("echo 0 > /sys/devices/platform/hud/display");
        system("echo 1 > /sys/class/backlight/backlight/bl_power");
    }
    else
    {
        system("echo 0 > /sys/class/backlight/backlight/bl_power");
        system("echo 1 > /sys/devices/platform/hud/display");
    }
}

void MainWindow::BatteryInit()
{
    // load setting_battery.json
    ConfigManager config = ConfigManager("setting_battery.json");
    QJsonObject object = config.GetConfig();

    double dVoltageThreasholdMax = object["VoltageThreasholdMax"].toDouble();
    double dVoltageThreasholdMin = object["VoltageThreasholdMin"].toDouble();
    int nChargeThreasholdMax = object["ChargeThreasholdMax"].toInt();
    int nChargeThreasholdMin = object["ChargeThreasholdMin"].toInt();

    //컨트롤 레지스터의 값을 읽어와서 정상값(236)과 비교한다
    if(ltc.readByteFromRegister(REG_B_CONTROL)!=236)//0x3C)
    {
        //컨트롤 레지스터에 값을 넣어준다
        ltc.setADCMode(ADC_MODE_AUTO);
        ltc.startMeasurement();
        ltc.configureALCC(ALCC_MODE_ALERT);
        ltc.setPrescalerM(1024);
    }

    if(ltc.readWordFromRegisters(REG_G_CHG_THR_L_MSB) != nChargeThreasholdMin)
    {
        //AC최대값 레지스터, AC 최소값 레지스터에 값을 넣는다.
        ltc.setChargeThresholds(nChargeThreasholdMax, nChargeThreasholdMin);

        //최대 전압 레지스터와 최소 전압 레지스터에 값을 넣는다.
        ltc.setVoltageThresholds(dVoltageThreasholdMax, dVoltageThreasholdMin);

        //컨트롤 레지스터와 AC레지스터에 값을 넣어준다
        //컨트롤 레지스터에 값을 넣어준다
        ltc.setADCMode(ADC_MODE_AUTO);
        ltc.startMeasurement();
        ltc.configureALCC(ALCC_MODE_ALERT);
        ltc.setPrescalerM(1024);

        for(int i =0; i<5; i++)
        {
            //get raw values
            ltc.getValues();

            //moving average filter
            ltc.filterValues();

            //조절해야함
            usleep(10000);
        }

        ltc.presetAC(ltc.m_filteredVolt*1000, ltc.getVoltageThresholdHigh()*1000, ltc.getVoltageThresholdLow()*1000);
    }

}

void MainWindow::ChechMainMenuImage()
{
    ConfigManager configManaer1 = ConfigManager("parameter_setting1.json");
    ConfigManager configManaer2 = ConfigManager("parameter_setting2.json");

    QJsonObject object1 = configManaer1.GetConfig();
    QJsonObject object2 = configManaer2.GetConfig();

    switch (object1["enforcement selection"].toInt())
    {
    case 1:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pEnforcementPushbutton, "indicator", "indicator_mode_i.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pEnforcementPushButton, "indicator", "indicator_mode_i.jpg");
    }
        break;
    case 2:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pEnforcementPushbutton, "indicator", "indicator_mode_a.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pEnforcementPushButton, "indicator", "indicator_mode_a.jpg");
    }
        break;
    case 3:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pEnforcementPushbutton, "indicator", "indicator_mode_v.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pEnforcementPushButton, "indicator", "indicator_mode_v.jpg");
    }
        break;
    }

    switch (object1["speed selection"].toInt())
    {
    case 1:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pSpeedPushbutton, "indicator", "indicator_enable_user_mode_on.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pSpeedModePushButton, "indicator", "indicator_enable_user_mode_on.jpg");
    }

        break;
    case 2:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pSpeedPushbutton, "indicator", "indicator_enable_user_mode_off.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pSpeedModePushButton, "indicator", "indicator_enable_user_mode_off.jpg");
    }
        break;
    }
    switch (object2["day&night selection"].toInt())
    {
    case 1:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "day1.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pDaynNightPushButton, "indicator", "day1.jpg");
    }
        break;
    case 2:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "day2.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pDaynNightPushButton, "indicator", "day2.jpg");
    }
        break;
    case 3:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "day3.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pDaynNightPushButton, "indicator", "day3.jpg");
    }
        break;
    case 4:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "night1.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pDaynNightPushButton, "indicator", "night1.jpg");
    }
        break;
    case 5:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "night2.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pDaynNightPushButton, "indicator", "night2.jpg");
    }
        break;
    case 6:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pDaynNightPushbutton, "indicator", "night3.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pDaynNightPushButton, "indicator", "night3.jpg");
    }
        break;
    }

    switch (object2["weather selection"].toInt())
    {
    case 1:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pWeatherPushbutton, "indicator", "indicator_enable_weather_mode_off.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pWeatherPushButton, "indicator", "indicator_enable_weather_mode_off.jpg");
    }
        break;
    case 2:
    {
        m_pMainMenuWidget->setIndicatorImage(m_pMainMenuWidget->m_pWeatherPushbutton, "indicator", "indicator_enable_weather_mode_on.jpg");
        m_pIndicatorWidget->setIndicatorImage(m_pIndicatorWidget->m_pWeatherPushButton, "indicator", "indicator_enable_weather_mode_on.jpg");
    }
        break;
    }
}

void MainWindow::SetCamera()
{
    if (!m_pCamera)
        m_pCamera = new Camera(this);
    m_pCamera->setGeometry(GetWidgetSizePos(QRect(0, 0, 1600, 960)));
    m_pCamera->lower();
    m_pCamera->show();
}

void MainWindow::SetRedLine()
{
//    QPainter painter(this);
//    QPen Pen(Qt::red);
//    Pen.setStyle(Qt::SolidLine);
//    Pen.setWidth(10);

//    painter.setPen(Pen);
//    painter.drawRect(GetWidgetSizePos(QRect(0, 0, 1600, 960)));

    this->setStyleSheet("QMainWindow{border: 1px solid red;}");
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
    QString filename = GetSubPath("manual_capture", SD) + "/" + GetFileName(SC);
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
        QString file_name = GetSubPath("screen", SD) + "/" + GetFileName(SR);
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

//    CheckPowerSavingTime();
}

void MainWindow::OnTimer500msFunc()
{
    CheckBatteryPercent();

    QTime time = time.currentTime();
    if (time.hour() == 0)
        g_nCrackDownIndex = 1;
}

void MainWindow::afterWindowShown()
{
    CheckLoginExpired();
}

void MainWindow::on_SystemInfoClicked()
{

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
    ui->verticalLayout->addWidget(pFileManagerWidget, 835);

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
    QObject::connect((QWidget*)pSettingWidget->m_pSetting3Widget, SIGNAL(clicked()), this, SLOT(on_SystemInfoClicked()));

    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_SETTING"));
}

//void MainWindow::on_mainMenuTitlePushButton_clicked()
//{
//    initializeMainMenuWidget();
//}

void MainWindow::on_device_id_clicked()
{
    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }

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
    m_widgetType = CameraAlign;
    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }

    m_p100msTimer->stop();
    m_p500msTimer->stop();

//    SetCamera();

//    m_pMainMenuWidget->hide();
    delete m_pMainMenuWidget;
    m_pMainMenuWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(0));
    delete m_pMainMenuAdminAlignWidget;
    m_pMainMenuAdminAlignWidget = nullptr;
//    ui->verticalLayout->setStretch(0, 0);
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));

    if (m_pCameraAlignWidget == nullptr)
        m_pCameraAlignWidget = new CameraAlignWidget(this);
    m_pCameraAlignWidget->setPSerialLaserManager(m_pSerialLaserManager);
    ui->verticalLayout->addWidget(m_pCameraAlignWidget, 960);
    SetCamera();

//    ui->verticalLayout->r
//    m_pCameraAlignWidget->setGeometry(GetWidgetSizePos(QRect(0, 0, 1600, 960)));
//    m_pCameraAlignWidget->raise();
//    m_pCameraAlignWidget->show();

//    ui->verticalLayout->addWidget(m_pCameraAlignWidget, 960);
    QObject::connect((QWidget*)m_pCameraAlignWidget->m_pHomeButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));
    QObject::connect((QWidget*)m_pCameraAlignWidget->m_pSaveButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));
    QObject::connect((QWidget*)m_pCameraAlignWidget->m_pCancelButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));
}

void MainWindow::on_camera_zoom_focus()
{
    if (m_pMainMenuAdminAlignWidget)
    {
        delete m_pMainMenuAdminAlignWidget;
        m_pMainMenuAdminAlignWidget = nullptr;
    }


    m_pMainMenuWidget->hideButton();
    m_pMainMenuWidget->setTransparentBackGround(true);

    delete m_pMainMenuAdminAlignWidget;
    m_pMainMenuAdminAlignWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    CameraZoomFocusWidget* pCameraZoonFocusWidget = new CameraZoomFocusWidget;
    ui->verticalLayout->addWidget(pCameraZoonFocusWidget, 835);
    pCameraZoonFocusWidget->setPSerialLaserManager(m_pSerialLaserManager);
    SetCamera();
    pCameraZoonFocusWidget->SetCamera(m_pCamera);
    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");

    showIndicator(false);
}

void MainWindow::on_SettingSaveClicked()
{
    CheckPowerSavingTime();

    ChechMainMenuImage();

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
    if (m_pCamera != nullptr)
    {
        delete m_pCamera;
        m_pCamera = nullptr;
    }

    if (m_widgetType == CameraAlign)
    {
        m_pMainMenuWidget = new MainMenuWidget;
        ui->verticalLayout->addWidget(m_pMainMenuWidget, 125);
        m_p100msTimer->start(100);
        m_p500msTimer->start(500);
    }
    if (m_widgetType == Enforcement)
        m_pMainMenuWidget->setTransparentBackGround(false);
    showIndicator(true);

    QWidget* widget = nullptr;
    if (ui->verticalLayout->count() > 1)
        widget = ui->verticalLayout->itemAt(1)->widget();

    if (m_pCameraAlignWidget)
    {
        delete m_pCameraAlignWidget;
        m_pCameraAlignWidget = nullptr;
    }

    if (m_pCamera)
    {
        delete m_pCamera;
        m_pCamera = nullptr;
    }

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

void MainWindow::on_ShowRedOutLine(bool bOn)
{
    if (bOn)
    {
        m_pMainMenuWidget->setRedLine(true);
//        ui->centralWidget->setStyleSheet("{border: 3px solid red;}");
    }
    else
    {
        m_pMainMenuWidget->setRedLine(false);
//        this->setStyleSheet("QMainWindow{border: none;}");
    }
    m_bRedLine = bOn;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    SetWindowWarningMode();

    if (m_bSelfTestFailed)
    {
//        SelfTestFail(m_bFlick);
        m_bFlick = !m_bFlick;
    }

//    QTime time;
//    time.
//    m_nSecond++;

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
    QPainter painter(this);
    //    painter.fillRect(rect(), QBrush(QColor(255, 0, 0, 128)));

    if (m_bRedLine)
    {
        QPen Pen(Qt::red);
        Pen.setStyle(Qt::SolidLine);
        Pen.setWidth(10);

        painter.setPen(Pen);
        painter.drawRect(this->geometry());

    }
//    painter.drawLine(gap, gap, getScreenWidth() - 2 * gap, gap);
//    painter.drawLine(gap, gap, gap, getScreenHeight());
//    painter.drawLine(getScreenWidth() - gap, gap, getScreenWidth() - 2 * gap, getScreenHeight() - 2 * gap);
//    painter.drawLine(gap, getScreenHeight() - 2 * gap, getScreenWidth() - 2 * gap, getScreenHeight() - 2 * gap);

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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    m_nCheckSecond = 0;
//    qDebug() << "press" << sec;
//    if (m_bPowerSavingMode == true)
//    {
//        SetPowerSavingMode(false);
//        m_bPowerSavingMode = false;
    //    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    QMetaObject::invokeMethod(this, "afterWindowShown", Qt::ConnectionType::QueuedConnection);
}

void MainWindow::get(screensaver *f)
{
    m_screensaver=f;
}
