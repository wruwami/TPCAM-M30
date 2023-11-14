#include "SettingWidget.h"
#include "ui_SettingWidget.h"

#include "Setting1Widget.h"
#include "Setting2Widget.h"
#include "Setting3Widget.h"
#include "Setting4APWidget.h"
#include "Setting4STAWidget.h"
#include "Setting5Widget.h"
#include "Setting6Widget.h"
#include "Setting7Widget.h"

#include "StringLoader.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include "NetworkManager.h"
#include "LcdBrightManager.h"

#include "WidgetSize.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    m_config = ConfigManager("parameter_setting4.json");

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->setting1PushButton->setFontSize(23);
    ui->setting2PushButton->setFontSize(23);
    ui->setting3PushButton->setFontSize(23);
    ui->setting4PushButton->setFontSize(23);
    ui->setting5PushButton->setFontSize(23);
    ui->setting6PushButton->setFontSize(23);
    ui->setting7PushButton->setFontSize(23);

    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->savePushButton->setFontSize(23);
    ui->cancelPushButton->setFontSize(23);



    m_pSetting1Widget = new Setting1Widget;
    m_pSetting2Widget = new Setting2Widget;
    m_pSetting3Widget = new Setting3Widget;
    m_pSetting4APWidget = new Setting4APWidget;
    m_pSetting4StaWidget = new Setting4STAWidget;
    m_pSetting5Widget = new Setting5Widget;
    m_pSetting6Widget = new Setting6Widget;
    m_pSetting7Widget = new Setting7Widget;
    ui->stackedWidget->addWidget(m_pSetting1Widget);
    ui->stackedWidget->addWidget(m_pSetting2Widget);
    ui->stackedWidget->addWidget(m_pSetting3Widget);
    QJsonObject jsonObject = m_config.GetConfig();
    QString wifi_mode = jsonObject["wifi_mode"].toString();
    if (wifi_mode == "AP")
        ui->stackedWidget->addWidget(m_pSetting4APWidget);
    else
        ui->stackedWidget->addWidget(m_pSetting4StaWidget);

    ui->stackedWidget->addWidget(m_pSetting5Widget);
    ui->stackedWidget->addWidget(m_pSetting6Widget);
    ui->stackedWidget->addWidget(m_pSetting7Widget);

    m_pSavePushButton = ui->savePushButton;
    m_pCancelPushButton = ui->cancelPushButton;

    clearStyleSheet();
    ui->setting1PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");

    m_pSetting3SystemButton = m_pSetting3Widget->m_pSystemInfoButton;

    //
    WidgetSize* ws = WidgetSize::GetInstance();
    ui->setting2PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));
    ui->setting3PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));
    ui->setting1PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));
    ui->setting4PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));
    ui->setting5PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));
    ui->setting6PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));
    ui->setting7PushButton->setFixedSize(ws->GetWidgetWidth(110), ws->GetWidgetHeight(110));

}

SettingWidget::~SettingWidget()
{
    delete m_pSetting1Widget;
    delete m_pSetting2Widget;
    delete m_pSetting3Widget;
    delete m_pSetting4APWidget;
    delete m_pSetting4StaWidget;
    delete m_pSetting5Widget;
    delete m_pSetting6Widget;
    delete m_pSetting7Widget;

//    for (int i = 0 ; i < 7 ; i++)
//    {
//        QWidget* widget = ui->stackedWidget->widget(i);
//        ui->stackedWidget->removeWidget(widget);
//        delete widget;
//        widget = nullptr;
//    }

    delete ui;
}

void SettingWidget::clearStyleSheet()
{
    ui->setting1PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
    ui->setting2PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
    ui->setting3PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
    ui->setting4PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
    ui->setting5PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
    ui->setting6PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
    ui->setting7PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 2px; border-color: blue; border-style: solid;}");
}

void SettingWidget::on_setting1PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clearStyleSheet();
    ui->setting1PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_setting2PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    clearStyleSheet();
    ui->setting2PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_setting3PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    clearStyleSheet();
    ui->setting3PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_setting4PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    clearStyleSheet();
    ui->setting4PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_setting5PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    clearStyleSheet();
    ui->setting5PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_setting6PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    clearStyleSheet();
    ui->setting6PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_setting7PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    clearStyleSheet();
    ui->setting7PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 2px; border-color : red;}");
}

void SettingWidget::on_stackedWidget_currentChanged(int arg1)
{

}

void SettingWidget::on_savePushButton_clicked()
{
    m_pSetting1Widget->SaveConfig();
    m_pSetting2Widget->SaveConfig();
    m_pSetting3Widget->SaveConfig();

    QString wifi_mode = ConfigManager("parameter_setting4.json").GetConfig()["wifi_mode"].toString();
    if (wifi_mode == "AP")
    {
        m_pSetting4APWidget->SaveConfig();
    }
    else
    {
        m_pSetting4StaWidget->SaveConfig();
    }
    m_pSetting5Widget->SaveConfig();
    m_pSetting6Widget->SaveConfig();
    m_pSetting7Widget->SaveConfig();

    NetworkManager networkManager;
    networkManager.SetNetworkSetting();

    LcdBrightManager lcdBrightManager;

    HUDManager hudManager;
    hudManager.SetDistanceSensitivityUnit();
    hudManager.SetDistanceUnit();
    hudManager.SetSpeedUnit();


//    ConfigManager configManaer1 = ConfigManager("parameter_settings1.json");
//    QJsonObject object = configManaer1.GetConfig();
    m_pSetting6Widget->initializeStringTable();
//    QJsonObject jsonObject = ConfigManager("parameter_settings6.json").GetConfig();
//    int index = jsonObject["language select"].toInt() - 1;
//    ResourceLoader::StringLoader::GetInstance()->Initialize("strings", "stringTable.csv", jsonObject["start language items"].toArray()[index].toString().toStdString());
}

void SettingWidget::on_cancelPushButton_clicked()
{

}
