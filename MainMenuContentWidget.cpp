#include "MainMenuContentWidget.h"
#include "ui_MainMenuContentWidget.h"

#include "ImageLoader.h"
#include "SettingWidget.h"
#include "FileManagementWidget.h"
#include "EnforcementWidget.h"

MainMenuContentWidget::MainMenuContentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuContentWidget)
{
    ui->setupUi(this);

    m_pEnforcementButton = ui->enforcementPushButton;

//    ui->settingPushButton->setStyleSheet(QString("QPushbutton {background-color: rgba(255,255,255,0); background-image: url(\"Main_menu\mainmenu_setting.bmp\");}"));
    ui->settingPushButton->setImage("Main_menu", "mainmenu_setting.bmp");
    ui->fileManagementPushButton->setImage("Main_menu", "mainmenu_file_management.bmp");
    ui->enforcementPushButton->setImage("Main_menu", "mainmenu_enforcement.bmp");
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
