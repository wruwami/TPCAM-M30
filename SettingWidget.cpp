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

    ui->stackedWidget->addWidget(new Setting1Widget);
    ui->stackedWidget->addWidget(new Setting2Widget);
    ui->stackedWidget->addWidget(new Setting3Widget);
    ui->stackedWidget->addWidget(new Setting4APWidget);
    ui->stackedWidget->addWidget(new Setting5Widget);
    ui->stackedWidget->addWidget(new Setting6Widget);
    ui->stackedWidget->addWidget(new Setting7Widget);

    m_pSavePushButton = ui->savePushButton;
    m_pCancelPushButton = ui->cancelPushButton;
}

SettingWidget::~SettingWidget()
{
    for (int i = 0 ; i < 7 ; i++)
    {
        QWidget* widget = ui->stackedWidget->widget(i);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }

    delete ui;
}

void SettingWidget::on_setting1PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void SettingWidget::on_setting2PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void SettingWidget::on_setting3PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void SettingWidget::on_setting4PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void SettingWidget::on_setting5PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void SettingWidget::on_setting6PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void SettingWidget::on_setting7PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


//void SettingWidget::on_savePushButton_clicked()
//{
////    accept();
//}


//void SettingWidget::on_cancelPushButton_clicked()
//{
////    reject();
//}

