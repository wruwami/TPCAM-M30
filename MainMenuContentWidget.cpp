#include "MainMenuContentWidget.h"
#include "ui_MainMenuContentWidget.h"

#include "SettingWidget.h"
#include "FileManagementWidget.h"
#include "EnforcementWidget.h"

MainMenuContentWidget::MainMenuContentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuContentWidget)
{
    ui->setupUi(this);
}

MainMenuContentWidget::~MainMenuContentWidget()
{
    delete ui;
}

void MainMenuContentWidget::on_settingPushButton_clicked()
{

}

void MainMenuContentWidget::on_fileManagementPushButton_clicked()
{

}

void MainMenuContentWidget::on_enforcementPushButton_clicked()
{

}
