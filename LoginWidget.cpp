#include "LoginWidget.h"
#include "ui_LoginWidget.h"

#include "Color.h"
#include "IndicatorWidget.h"
#include "MainWindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0xf2f2f2);
    m_parent = parent;
    m_loginPushButton = ui->loginPushButton;
}

LoginWidget::~LoginWidget()
{
    delete m_loginPushButton;
    delete ui;
}

void LoginWidget::on_loginPushButton_clicked()
{
//    m_parent->ui->verticalLayout_2->removeWidget(m_pLoginWidget);
//    IndicatorWidget indicatorWidget;
//    m_paremt->ui->verticalLayout_2->addWidget(&indicatorWidget, 835);
    close();
//    (MainWindow*)m_parent->
//    ~LoginWidget();
}
