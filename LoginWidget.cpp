#include "LoginWidget.h"
#include "ui_LoginWidget.h"

#include <QJsonArray>
#include <QFile>
#include <QDateTime>

#include "Color.h"
#include "StringLoader.h"
#include "IndicatorDialog.h"
#include "MainWindow.h"
#include "StringLoader.h"
#include "BaseDialog.h"
#include "KeyboardDialog.h"
#include "KeypadDialog.h"
#include "FileManager.h"
#include "LightManager.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();

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
    ui->deviceIDLineEdit->setText(m_jsonObject["Device ID"].toString());

    foreach(QJsonValue json, m_jsonObject["User Name items"].toArray())
    {
        ui->userNameComboBox->addItem(json.toString());
        ItemPush(json.toString());
    }
    ui->userNameComboBox->setCurrentIndex(m_jsonObject["User Name Select"].toInt() - 1);

    m_pLightMager = new LightManager;

//    m_userName = ui->userNameComboBox->it;
}

LoginWidget::~LoginWidget()
{
    m_config.SetConfig(m_jsonObject);
    m_config.SaveFile();
    if (m_pLightMager != nullptr)
    {
        delete m_pLightMager;
        m_pLightMager = nullptr;
    }
    delete m_loginPushButton;
    delete m_dateTimePushButton;
    delete ui;
}

void LoginWidget::ItemPush(QString item)
{
    if (m_queue.size() < 5 )
    {
        m_queue.push_back(item);
    }
    else
    {
        m_queue.dequeue();
        m_queue.push_back(item);
    }
}

void LoginWidget::on_loginPushButton_clicked()
{
//    m_parent->ui->verticalLayout_2->removeWidget(m_pLoginWidget);
//    IndicatorWidget indicatorWidget;
//    m_parent->ui->verticalLayout_2->addWidget(&indicatorWidget, 835);
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
    m_pLightMager->SwapLight();
}

void LoginWidget::on_userNamePushButton_clicked()
{
    KeyboardDialog keyboardDialog(GetLanguage());
    if (keyboardDialog.exec() == QDialog::Accepted)
    {
        ItemPush(keyboardDialog.str());
    }
    ui->userNameComboBox->clear();
    QJsonArray array = m_jsonObject["User Name items"].toArray();

    while(array.count()) {
        array.pop_back();
    }
    foreach( auto item , m_queue)
    {
        ui->userNameComboBox->addItem(item);
        array.push_back(item);
    }
    m_jsonObject["User Name items"] = array;
} 

//void LoginWidget::on_userNameComboBox_currentIndexChanged(const QString &arg)
//{
//    m_userName = arg;
//}
