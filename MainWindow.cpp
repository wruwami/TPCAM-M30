#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>

#include "LoginWidget.h"
#include "MainMenuContentWidget.h"
#include "DateTimeWidget.h"
#include "MainMenuWidget.h"
#include "EnforcementWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLoginWidget = new LoginWidget;
//    m_pMainMenuContentWidget = new MainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(m_pLoginWidget, 835);

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
    ui->verticalLayout->addWidget(new MainMenuWidget, 125);
    ui->verticalLayout->addWidget(new MainMenuContentWidget, 835);
    ui->centralWidget->setLayout(layout);
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

void MainWindow::on_cameraPushButton_clicked()
{

}

void MainWindow::on_daynNightPushButton_clicked()
{

}

void MainWindow::on_loginWidgetClose()
{
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    m_pMainMenuContentWidget = new MainMenuContentWidget;
    ui->verticalLayout->addWidget(m_pMainMenuContentWidget, 835);
    QObject::connect((QWidget*)m_pMainMenuContentWidget->m_pEnforcementButton, SIGNAL(clicked()), this, SLOT(on_enforcementClicked()));
}

void MainWindow::on_dateTimeWidgetClicked()
{
    DateTimeWidget dateTimeWidget;
    dateTimeWidget.setGeometry(ui->verticalLayout->itemAt(1)->geometry());
    dateTimeWidget.exec();
}

void MainWindow::on_enforcementClicked()
{
//    finalize();

    delete m_pMainMenuContentWidget;
    ui->verticalLayout->removeItem(ui->verticalLayout->itemAt(1));
    ui->verticalLayout->addWidget(new EnforcementWidget, 835);
//    m_pMainMenuContentWidget = new MainMenuContentWidget;
//    QVBoxLayout* layout = new QVBoxLayout;
//    layout->addWidget(new EnforcementWidget);
//    ui->centralWidget->setLayout(layout);
}
