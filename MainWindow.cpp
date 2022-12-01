#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>

#include "DateTimeWidget.h"
#include "EnforcementWidget.h"
#include "IndicatorWidget.h"
#include "MainMenuWidget.h"
#include "MainMenuContentWidget.h"
#include "LoginWidget.h"
#include "FileManagerWidget.h"
#include "SettingWidget.h"

#include "StringLoader.h"

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


    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClose()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));

}

MainWindow::~MainWindow()
{
//    if (m_pLoginWidget != nullptr)
//        delete m_pLoginWidget;
//    if (m_pMainMenuContentWidget != nullptr)
//        delete m_pMainMenuContentWidget;

    finalize();

    delete ui;
}

void MainWindow::initialize()
{
    QVBoxLayout* layout = new QVBoxLayout;
    MainMenuWidget* mainMenuWidget = new MainMenuWidget;
//    mainMenuWidget->setEnabled(true);
    ui->verticalLayout->addWidget(mainMenuWidget, 125);
    ui->verticalLayout->addWidget(new MainMenuContentWidget, 835);
    ui->centralWidget->setLayout(layout);

    QObject::connect((QWidget*)mainMenuWidget->m_pCameraPushbutton, SIGNAL(clicked()), this, SLOT(on_cameraPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pDaynNightPushbutton, SIGNAL(clicked()), this, SLOT(on_daynNightPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pWeatherPushbutton, SIGNAL(clicked()), this, SLOT(on_weatherPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pEnforcementPushbutton, SIGNAL(clicked()), this, SLOT(on_enforcementPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pSpeedPushbutton, SIGNAL(clicked()), this, SLOT(on_speedPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pWifiPushbutton, SIGNAL(clicked()), this, SLOT(on_wifiPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pGpsPushbutton, SIGNAL(clicked()), this, SLOT(on_gpsPushButton_clicked()));
    QObject::connect((QWidget*)mainMenuWidget->m_pMainMenuTitlePushButton, SIGNAL(clicked()), this, SLOT(on_mainMenuTitlePushButton_clicked()));
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
    IndicatorWidget indicatorWidget;
    indicatorWidget.setGeometry(ui->verticalLayout->itemAt(1)->widget()->geometry());
    indicatorWidget.exec();
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

void MainWindow::on_loginWidgetClose()
{
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    m_pMainMenuContentWidget = new MainMenuContentWidget;
    ui->verticalLayout->addWidget(m_pMainMenuContentWidget, 835);
    QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pEnforcementButton, SIGNAL(clicked()), this, SLOT(on_enforcementClicked()));
    QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pFileManagertButton, SIGNAL(clicked()), this, SLOT(on_filemanagementClicked()));
    QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pSettingButton, SIGNAL(clicked()), this, SLOT(on_settingClicked()));
}

void MainWindow::on_dateTimeWidgetClicked()
{
    DateTimeWidget dateTimeWidget;
    dateTimeWidget.setGeometry(ui->verticalLayout->itemAt(1)->geometry());
    dateTimeWidget.exec();
}

void MainWindow::on_enforcementClicked()
{
    delete m_pMainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new EnforcementWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::on_filemanagementClicked()
{
    delete m_pMainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new FileManagerWidget, 835);

    m_pMainMenuWidget->setMainMenuImage("Main_menu", "home_big_n.bmp");
}

void MainWindow::on_settingClicked()
{
    delete m_pMainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new SettingWidget, 835);

    m_pMainMenuWidget->setMainMenuTitle(LoadString("IDS_SETTING"));
}

void MainWindow::on_mainMenuTitlePushButton_clicked()
{
    initialize();
}
