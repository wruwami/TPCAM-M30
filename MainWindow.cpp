#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LoginWidget.h"
#include "MainMenuContentWidget.h"
#include "DateTimeWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLoginWidget = new LoginWidget;
    ui->verticalLayout_2->removeItem(ui->verticalLayout_2->itemAt(1));
    ui->verticalLayout_2->addWidget(m_pLoginWidget, 835);

//    m_dateTimeWidget = new DateTimeWidget;

    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClose()));
    QObject::connect((QWidget*)m_pLoginWidget->m_dateTimePushButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
//    QObject::connect((QWidget*)m_dateTimeWidget->m_cancelButton, SIGNAL(clicked()), this, SLOT(on_dateTimeWidgetClicked()));
}

MainWindow::~MainWindow()
{
    if (m_pLoginWidget != nullptr)
        delete m_pLoginWidget;
    if (m_dateTimeWidget != nullptr)
        delete m_dateTimeWidget;
    delete ui;
}

void MainWindow::on_cameraPushButton_clicked()
{

}

void MainWindow::on_daynNightPushButton_clicked()
{

}

void MainWindow::on_loginWidgetClose()
{
    ui->verticalLayout_2->removeItem(ui->verticalLayout_2->itemAt(1));
    m_pMainMenuContentWidget = new MainMenuContentWidget();
    ui->verticalLayout_2->addWidget(m_pMainMenuContentWidget, 835);
}

void MainWindow::on_dateTimeWidgetClicked()
{
//    ui->verticalLayout_2->removeItem(ui->verticalLayout_2->takeAt(1));

//    ui->verticalLayout_2->addWidget(m_dateTimeWidget, 835);
    DateTimeWidget dateTimeWidget;
    dateTimeWidget.setGeometry(ui->verticalLayout_2->itemAt(1)->geometry());
    dateTimeWidget.exec();
}

void MainWindow::on_dateTimeWidgetCanceled()
{
//    ui->verticalLayout_2->removeItem(ui->verticalLayout_2->takeAt(1));

//    ui->verticalLayout_2->addWidget(m_pLoginWidget, 835);
    DateTimeWidget dateTimeWidget;
//    dateTimeWidget.setGeometry(ui->verticalLayout_2->takeAt(1)->geometry());
    dateTimeWidget.exec();
}
