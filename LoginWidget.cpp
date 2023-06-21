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
//        ItemBackPush(json.toString());
    }
    ui->userNameComboBox->setCurrentIndex(m_jsonObject["User Name Select"].toInt() - 1);

    m_pLightMager = new LightManager;

//    m_userName = ui->userNameComboBox->it;
}

LoginWidget::~LoginWidget()
{

    if (m_pLightMager != nullptr)
    {
        delete m_pLightMager;
        m_pLightMager = nullptr;
    }
    delete m_loginPushButton;
    delete m_dateTimePushButton;
    delete ui;
}

//void LoginWidget::ItemBackPush(QString item)
//{
//    if (m_queue.size() < 5 )
//    {
//        m_queue.push_front(item);
//    }
//    else
//    {
//        m_queue.pop_back();
//        m_queue.push_front(item);
//    }
//}

//void LoginWidget::ItemFrontPush(QString item)
//{
//    if (m_queue.size() < 5 )
//    {
//        m_queue.push_front(item);
//    }
//    else
//    {
//        m_queue.pop_back();
//        m_queue.push_front(item);
//    }
//}

void LoginWidget::on_loginPushButton_clicked()
{
//    m_parent->ui->verticalLayout_2->removeWidget(m_pLoginWidget);
//    IndicatorWidget indicatorWidget;
//    m_parent->ui->verticalLayout_2->addWidget(&indicatorWidget, 835);
    m_config.SetConfig(m_jsonObject);
    m_config.SaveFile();
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

//void LoginWidget::CheckLoginExpired()
//{
//    ConfigManager configManager = ConfigManager("expired_date.txt");
//    QString str = configManager.GetText();
//    if (str.isEmpty())
//        return;

//    if (str.at(str.size() - 1) == '\n')
//    {
//        str.remove(str.size() - 1, 1);
//    }
////    QFile expired_file(GetPath("", SD) + "/" + ("expired_date.txt"));
////    expired_file.open(QFile::ReadOnly);

////    if (expired_file.isOpen())
////    {
////        expired_file.copy(GetPath("", eMMC) + "/" + expired_file.Text);
////        expired_file.remove();
//////        ui->expiredDateLabel->setText(LoadString("IDS_EXPIRED_DATE"));
////    }
////    else
////    {

////    }
//////    expired_file.close();

////    QByteArray ba = expired_file.readAll();
////    QString str = QString(ba);
//    QDateTime datetime;
//    ;
//    QDateTime current_datetime;

//    qDebug() << current_datetime.currentDateTime();
//    qDebug() << datetime.fromString(str, "yyyyMMdd");

//    if (current_datetime.currentDateTime() > datetime.fromString(str, "yyyyMMdd"))
//    {
//        BaseDialog baseDialog(Dialog::LoginExpiredDateWidgetType, Qt::AlignmentFlag::AlignLeft, "", false, LoadString("IDS_EXPIRED_DATE"));
//        baseDialog.exec();
//    }

//}


void LoginWidget::on_userNamePushButton_clicked()
{
    KeyboardDialog keyboardDialog(ui->userNameComboBox->currentText(), GetLanguage());
    if (keyboardDialog.exec() == QDialog::Accepted)
    {
        ui->userNameComboBox->removeItem(4);
        ui->userNameComboBox->insertItem(0, keyboardDialog.str());

//        ItemBackPush(keyboardDialog.str());
//        m_queue.removeAt(ui->userNameComboBox->currentIndex());
    }
    QJsonArray array = m_jsonObject["User Name items"].toArray();

    while(array.count()) {
        array.pop_back();
    }
    for (int i = 0 ; i < ui->userNameComboBox->count() ; i++)
    {
        array.push_back(ui->userNameComboBox->itemText(i));
    }
    m_jsonObject["User Name items"] = array;
    m_jsonObject["User Name Select"] = ui->userNameComboBox->currentIndex() + 1;
    ui->userNameComboBox->setCurrentIndex(0);

} 

//void LoginWidget::on_userNameComboBox_currentIndexChanged(const QString &arg)
//{
//    m_userName = arg;
//}

void LoginWidget::on_userNameComboBox_currentIndexChanged(int index)
{
    m_jsonObject["User Name Select"] = index + 1;
}

