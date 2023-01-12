#include "LoginWidget.h"
#include "ui_LoginWidget.h"

#include "Color.h"
#include "StringLoader.h"
#include "IndicatorDialog.h"
#include "MainWindow.h"
#include "StringLoader.h"
#include "BaseDialog.h"
#include "KeyboardDialog.h"
#include "KeypadDialog.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0xf2f2f2);
    m_loginPushButton = ui->loginPushButton;
    m_dateTimePushButton = ui->dateTimePushButton;
    m_pUserNameComboBox = ui->userNameComboBox;

    ui->dateTimePushButton->setText(LoadString("IDS_DATE_TIME"));
    ui->lightPushButton->setText(LoadString("IDS_LIGHT"));

    // 추후 cfg와 연동하여 수정 필요
    ui->versionLabel->setText("v.1.0.0");

    ui->deviceIDLabel->setText(LoadString("IDS_DEVICE_ID"));
    ui->userNameLabel->setText(LoadString("IDS_USER_NAME"));

    ui->loginPushButton->setText(LoadString("IDS_LOGIN"));

    ui->userNamePushButton->setImage("Login", "keyboard.bmp");
    ui->logoLabel->setImage("Login", "comlaser_logo.bmp");
    ui->deviceIDLineEdit->setDisabled(true);

    //시연용
    ui->userNameComboBox->addItem("admin");
    ui->userNameComboBox->addItem("admin-align");

    ui->deviceIDLineEdit->setText("TP30001-00001");
    ui->userNameComboBox->addItem("NY-Man-Jo...");

//    m_userName = ui->userNameComboBox->it;
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
}

void LoginWidget::on_userNamePushButton_clicked()
{
    KeyboardDialog keyboardDialog(GetLanguage(), ui->userNameComboBox->currentText());
    keyboardDialog.exec();
}

//void LoginWidget::on_userNameComboBox_currentIndexChanged(const QString &arg)
//{
//    m_userName = arg;
//}
