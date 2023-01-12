#include "SettingWidget.h"
#include "ui_SettingWidget.h"

#include "Setting1Widget.h"
#include "Setting2Widget.h"
#include "Setting3Widget.h"
#include "Setting4APWidget.h"
#include "Setting5Widget.h"
#include "Setting6Widget.h"
#include "Setting7Widget.h"

#include "StringLoader.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

    m_pSetting1Widget = new Setting1Widget;
    m_pSetting2Widget = new Setting2Widget;
    m_pSetting3Widget = new Setting3Widget;
    m_pSetting4APWidget = new Setting4APWidget;
    m_pSetting5Widget = new Setting5Widget;
    m_pSetting6Widget = new Setting6Widget;
    m_pSetting7Widget = new Setting7Widget;
    ui->stackedWidget->addWidget(m_pSetting1Widget);
    ui->stackedWidget->addWidget(m_pSetting2Widget);
    ui->stackedWidget->addWidget(m_pSetting3Widget);
    ui->stackedWidget->addWidget(m_pSetting4APWidget);
    ui->stackedWidget->addWidget(m_pSetting5Widget);
    ui->stackedWidget->addWidget(m_pSetting6Widget);
    ui->stackedWidget->addWidget(m_pSetting7Widget);

    m_pSavePushButton = ui->savePushButton;
    m_pCancelPushButton = ui->cancelPushButton;

    clearStyleSheet();
    ui->setting1PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");

}

SettingWidget::~SettingWidget()
{
    for (int i = 0 ; i < 7 ; i++)
    {
        QWidget* widget = ui->stackedWidget->widget(i);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
        widget = nullptr;
    }

    delete ui;
}

void SettingWidget::clearStyleSheet()
{
    ui->setting1PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
    ui->setting2PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
    ui->setting3PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
    ui->setting4PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
    ui->setting5PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
    ui->setting6PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
    ui->setting7PushButton->setStyleSheet("QPushButton { color: black; background-color: white; border-width: 1px; border-color: blue; border-style: solid;}");
}

void SettingWidget::on_setting1PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clearStyleSheet();
    ui->setting1PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_setting2PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    clearStyleSheet();
    ui->setting2PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_setting3PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    clearStyleSheet();
    ui->setting3PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_setting4PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    clearStyleSheet();
    ui->setting4PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_setting5PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    clearStyleSheet();
    ui->setting5PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_setting6PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    clearStyleSheet();
    ui->setting6PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_setting7PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    clearStyleSheet();
    ui->setting7PushButton->setStyleSheet("QPushButton{ color : black; background-color :white; border-style: solid; border-width: 1px; border-color : red;}");
}

void SettingWidget::on_stackedWidget_currentChanged(int arg1)
{

}

void SettingWidget::on_savePushButton_clicked()
{

}

void SettingWidget::on_cancelPushButton_clicked()
{

}
