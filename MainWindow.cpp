#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LoginWidget.h"
#include "IndicatorWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLoginWidget = new LoginWidget(this);
    ui->verticalLayout_2->addWidget(m_pLoginWidget, 835);

    QObject::connect((QWidget*)m_pLoginWidget->m_loginPushButton, SIGNAL(clicked()), this, SLOT(on_loginWidgetClose()));
}

MainWindow::~MainWindow()
{
    if (m_pLoginWidget != nullptr)
        delete m_pLoginWidget;
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
    ui->verticalLayout_2->removeWidget(m_pLoginWidget);
    m_pIndicatorWidget = new IndicatorWidget();
    ui->verticalLayout_2->addWidget(m_pIndicatorWidget, 835);
}
