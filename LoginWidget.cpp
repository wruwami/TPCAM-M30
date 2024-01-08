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
#include "Logger.h"

extern QString g_AppVersion;

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();

    setBackGroundColor(this, 0xffffff);
    m_loginPushButton = ui->loginPushButton;
    m_dateTimePushButton = ui->dateTimePushButton;
    m_pUserNameComboBox = ui->userNameComboBox;

    ui->dateTimePushButton->setText(LoadString("IDS_DATE_TIME"));
    ui->lightPushButton->setText(LoadString("IDS_LIGHT"));
    ui->dateTimePushButton->setFontSize(23);
    ui->lightPushButton->setFontSize(23);


    // 추후 cfg와 연동하여 수정 필요
    ui->versionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->versionLabel->setText(g_AppVersion);

    ui->deviceIDLabel->setText(LoadString("IDS_DEVICE_ID"));
    ui->userNameLabel->setText(LoadString("IDS_USER_NAME"));
    ui->loginPushButton->setText(LoadString("IDS_LOGIN"));
    ui->deviceIDLabel->setFontSize(23);
    ui->userNameLabel->setFontSize(23);
    ui->loginPushButton->setFontSize(23);

    ui->userNamePushButton->setImage("Login", "keyboard.bmp");
//    ui->logoLabel->setImage("Login", "comlaser_logo.bmp");

    QPixmap pixmap;
    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "Main_menu" + "/" + "comlaser_logo.bmp");
    ui->logoPushButton->setIcon(QIcon(pixmap));
    ui->logoPushButton->setIconSize(pixmap.rect()/*.adjusted(1, 1, -1, -1)*/.size());
    ui->logoPushButton->setStyleSheet("QPushButton {border : none;} QPushButton:pressed {border: 2px solid red;}");
    ui->logoPushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->deviceIDLineEdit->setDisabled(true);

    QJsonObject object = ConfigManager("setting_device_ID.json").GetConfig();
    QJsonObject object2 = object["Device ID"].toObject();
    QString SerialNum;

    if (QString::compare(object2["Prefix"].toString(), "null", Qt::CaseInsensitive) && !object2["Prefix"].toString().isEmpty())
        SerialNum.append(object2["Prefix"].toString() + "_" + object2["SerialNum"].toString());
    else
        SerialNum.append(object2["SerialNum"].toString());
    if (QString::compare(object2["Postfix"].toString(), "null", Qt::CaseInsensitive) && !object2["Postfix"].toString().isEmpty())
        SerialNum.append("_" + object2["Postfix"].toString());

    ui->deviceIDLineEdit->setText(SerialNum);
    ui->deviceIDLineEdit->setFontSize(23);


    int index = 0;
    QJsonArray ar = m_jsonObject["User Name items"].toArray();
//    ui->userNameComboBox->addItem(ar[index].toString());
//    ar.removeAt(index);

    foreach(QJsonValue json, ar)
    {
        ui->userNameComboBox->addItem(json.toString());
//        ItemBackPush(json.toString());
    }
    ui->userNameComboBox->setCurrentIndex(index);
    ui->userNameComboBox->setFontSize(23);
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

int LoginWidget::CheckComboxBoxItem(QString str)
{
    for (int i = 0 ; i < ui->userNameComboBox->count() ; i++)
    {
        if ( str  == ui->userNameComboBox->itemText(i))
            return i;
    }

    return -1;
//    foreach(auto item, ui->userNameComboBox)
//    {

//    }
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
    QJsonArray ar = m_jsonObject["User Name items"].toArray();
    QJsonValue jv = ar[m_nIndex];
    ar.removeAt(m_nIndex);
    ar.insert(0, jv);
    m_jsonObject["User Name Select"] = 1;
    m_jsonObject["User Name items"] = ar;
//    m_parent->ui->verticalLayout_2->removeWidget(m_pLoginWidget);
//    IndicatorWidget indicatorWidget;
//    m_parent->ui->verticalLayout_2->addWidget(&indicatorWidget, 835);

    if (m_StrKeyboard != "admin-test" && m_StrKeyboard != "admin-align" && m_StrKeyboard != "admin-vsg" && m_StrKeyboard != "admin-save")
    {
        m_config.SetConfig(m_jsonObject);
        m_config.SaveFile();
    }
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
//        if (ui->userNameComboBox->item)
        m_StrKeyboard = keyboardDialog.str();
        int index;
        if ((index = CheckComboxBoxItem(m_StrKeyboard)) == -1)
        {
            ui->userNameComboBox->removeItem(4);
            ui->userNameComboBox->insertItem(0, keyboardDialog.str());
        }
        else
        {
            ui->userNameComboBox->removeItem(index);
            ui->userNameComboBox->insertItem(0, keyboardDialog.str());
        }


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
//    m_jsonObject["User Name Select"] = ui->userNameComboBox->currentIndex() + 1;
    ui->userNameComboBox->setCurrentIndex(0);

} 

//void LoginWidget::on_userNameComboBox_currentIndexChanged(const QString &arg)
//{
//    m_userName = arg;
//}

void LoginWidget::on_userNameComboBox_currentIndexChanged(int index)
{
    m_nIndex = index;
}


void LoginWidget::on_logoPushButton_clicked()
{
    static int nclick = 0;
    ++nclick;
    if(nclick >= 3)
    {
        //        OS 자동 종료
        QEventLoop loop;
        SoundPlayer::GetInstance()->play(ReBooting);
        connect(SoundPlayer::GetInstance(), SIGNAL(audioStop()), &loop, SLOT(quit()));
        loop.exec();

        QProcess::startDetached("sudo shutdown -h now");
        SetLogMsg(POWER_OFF, "logo in loginWidget clicked 3 times");
    }
}
