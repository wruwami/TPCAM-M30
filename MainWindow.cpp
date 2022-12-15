#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>
#include <QPainter>

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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pMainMenuWidget = (MainMenuWidget*)ui->verticalLayout->itemAt(0)->widget();

    m_pLoginWidget = new LoginWidget;
//    m_pMainMenuContentWidget = new MainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(m_pLoginWidget, 835);
    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_LOGIN"));


    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
    QObject::connect((QWidget*)m_pLoginWidget->m_pUserNameComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_userNameChanged(QString)));
    QObject::connect((QWidget*)m_pMainMenuWidget->m_pHomePushButton, SIGNAL(clicked()), this, SLOT(on_mainMenuHomeClicked()));

//    SetWarningMode();

}

MainWindow::~MainWindow()
{
    if (m_pLoginWidget != nullptr)
        delete m_pLoginWidget;
    if (m_pMainMenuContentWidget != nullptr)
        delete m_pMainMenuContentWidget;

    delete m_pIndicatorCameraExposeWidget;
    delete m_pIndicatorCameraFocusWidget;

    finalize();

    delete ui;
}



void MainWindow::initializeMainMenuWidget()
{
    m_pMainMenuWidget->show();
    if (m_userName == "admin-align")
    {
        removeseconditem();

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
        removeseconditem();

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
    removeseconditem();
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
    m_pIndicatorWidget = new IndicatorDialog(this);
    m_pIndicatorWidget->setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 960)));

//    indicatorWidget.setGeometry(ui->centralWidget->geometry());
    m_pIndicatorWidget->show();

//    m_pIndicatorWidget->m_pCameraExposePushButton = new CustomPushButton;
//    m_pIndicatorWidget->m_pCameraFocusPushButton = new CustomPushButton;
//    QObject::connect((QWidget*)m_pIndicatorWidget->m_pCameraExposePushButton, SIGNAL(clicked()), this, SLOT(on_cameraExposeClicked()));
//    QObject::connect((QWidget*)m_pIndicatorWidget->m_pCameraFocusPushButton, SIGNAL(clicked()), this, SLOT(on_cameraFocusClicked()));
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
    removeseconditem();
//    ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(1));
//    if (m_pLoginWidget)
//    {
//        delete m_pLoginWidget;
//        m_pLoginWidget = nullptr;
//    }
//    if (m_pDateTimeWidget == nullptr)
    m_pDateTimeWidget = new DateTimeWidget;
    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_DATE_TIME"));
    ui->verticalLayout->addWidget(m_pDateTimeWidget, 835);
    QObject::connect((QWidget*)m_pDateTimeWidget->m_pSavePushButton, SIGNAL(clicked()), this, SLOT(on_DateTimeSaveClicked()));
    QObject::connect((QWidget*)m_pDateTimeWidget->m_pCancelPushButton, SIGNAL(clicked()), this, SLOT(on_DateTimeCancelClicked()));
}

void MainWindow::on_enforcementClicked()
{
    delete m_pMainMenuContentWidget;
    m_pMainMenuContentWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new EnforcementWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::on_filemanagementClicked()
{
    delete m_pMainMenuContentWidget;
    m_pMainMenuContentWidget = nullptr;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new FileManagerWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::on_settingClicked()
{
    delete m_pMainMenuContentWidget;
    m_pMainMenuContentWidget = nullptr;
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
    ui->verticalLayout->addWidget(new DeviceIDWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");

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

    if (m_pCameraAlignWidget)
    {
        delete m_pCameraAlignWidget;
        m_pCameraAlignWidget = nullptr;
    }

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

void MainWindow::on_cameraExposeClicked()
{
    if (m_pIndicatorCameraFocusWidget != nullptr)
    {
        delete m_pIndicatorCameraFocusWidget;
        m_pIndicatorCameraFocusWidget = nullptr;
    }

//    m_pIndicatorCameraExposeWidget = new IndicatorCameraExposeWidget(this);
//    m_pIndicatorCameraExposeWidget->setGeometry(GetWidgetSizePos(QRect(0, 272, 1600, 563)));
//    m_pIndicatorCameraExposeWidget->lower();
//    m_pIndicatorCameraExposeWidget->show();
    if (m_pIndicatorWidget)
    {
        m_pIndicatorWidget->close();
        delete m_pIndicatorWidget;
        m_pIndicatorWidget = nullptr;
    }

    IndicatorCameraExposeWidget indicatorCameraExposeWidget;
    indicatorCameraExposeWidget.exec();



}

void MainWindow::on_cameraFocusClicked()
{

    if (m_pIndicatorCameraExposeWidget != nullptr)
    {
        delete m_pIndicatorCameraExposeWidget;
        m_pIndicatorCameraExposeWidget = nullptr;
    }

//    m_pIndicatorCameraFocusWidget = new IndicatorCameraFocusWidget(this);
//    m_pIndicatorCameraFocusWidget->setGeometry(GetWidgetSizePos(QRect(0, 433, 1600, 402)));
//    m_pIndicatorCameraFocusWidget->lower();
//    m_pIndicatorCameraFocusWidget->show();

    if (m_pIndicatorWidget)
    {
        m_pIndicatorWidget->close();
        delete m_pIndicatorWidget;
        m_pIndicatorWidget = nullptr;
    }

    IndicatorCameraFocusWidget indicatorCameraFocusWidget;
    indicatorCameraFocusWidget.exec();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    SetWindowWarningMode();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
//    QPainter painter(this);
//    painter.fillRect(rect(), QBrush(QColor(255, 0, 0, 128)));
}
