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

    m_pEnforcementButton = ui->enforcementPushButton;
}

MainMenuContentWidget::~MainMenuContentWidget()
{
    delete ui;
}

void MainMenuContentWidget::on_settingPushButton_clicked()
{
    SettingWidget settingWidget;
    settingWidget.setGeometry(this->geometry());
    settingWidget.exec();
}

void MainMenuContentWidget::on_fileManagementPushButton_clicked()
{
    FileManagementWidget fileManagementWidget;
    fileManagementWidget.setGeometry(this->geometry());
    fileManagementWidget.exec();
}
