#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LoginWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLoginWidget = new LoginWidget();
    ui->verticalLayout_2->addWidget(m_pLoginWidget, 835);
}

MainWindow::~MainWindow()
{
    delete m_pLoginWidget;
    delete ui;
}

void MainWindow::on_cameraPushButton_clicked()
{

}

void MainWindow::on_daynNightPushButton_clicked()
{

}
