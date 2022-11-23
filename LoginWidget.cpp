#include "LoginWidget.h"
#include "ui_LoginWidget.h"

#include "Color.h"
#include "StringLoader.h"
#include "IndicatorWidget.h"
#include "MainWindow.h"
#include "StringLoader.h"
#include "BaseDialog.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0xf2f2f2);
    m_loginPushButton = ui->loginPushButton;
    m_dateTimePushButton = ui->dateTimePushButton;

    ui->dateTimePushButton->setText(LoadString("IDS_DATE_TIME"));
    ui->lightPushButton->setText(LoadString("IDS_LIGHT"));

    // 추후 cfg와 연동하여 수정 필요
    ui->versionLabel->setText("v.1.0.0");

    ui->deviceIDLabel->setText(LoadString("IDS_DEVICE_ID"));
    ui->userNameLabel->setText(LoadString("IDS_USER_NAME"));

    ui->loginPushButton->setText(LoadString("IDS_LOGIN"));
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

void LoginWidget::on_dateTimePushButton_clicked()
{
//    close();
}

void LoginWidget::on_lightPushButton_clicked()
{
//    QRect rect(100, 100, 400, 400);
    BaseDialog baseDialog(Dialog::LoginExpiredDateWidgetType);
    baseDialog.exec();
}
