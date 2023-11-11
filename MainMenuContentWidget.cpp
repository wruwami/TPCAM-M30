#include "MainMenuContentWidget.h"
#include "ui_MainMenuContentWidget.h"

#include "qdir.h"

#include "SettingWidget.h"
#include "FileManagerWidget.h"
#include "EnforcementWidget.h"
#include "FileManager.h"
#include "Color.h"

MainMenuContentWidget::MainMenuContentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuContentWidget)
{
    ui->setupUi(this);

    setBackGroundColor(this, 0xffffff);

    m_pEnforcementButton = ui->enforcementPushButton;
    m_pFileManagertButton = ui->fileManagerPushButton;
    m_pSettingButton = ui->settingPushButton;

//    ui->settingPushButton->setStyleSheet(QString("QPushbutton {background-color: rgba(255,255,255,0); background-image: url(\"Main_menu\mainmenu_setting.bmp\");}"));

//    QSize size = QSize(ui->horizontalLayout->itemAt(0)->geometry().width(), ui->horizontalLayout->itemAt(0)->geometry().height());
    ui->settingPushButton->setImage("Main_menu", "mainmenu_setting.bmp");
    ui->fileManagerPushButton->setImage("Main_menu", "mainmenu_file_management.bmp");
    ui->enforcementPushButton->setImage("Main_menu", "mainmenu_enforcement.bmp");

    m_pLogoButton = ui->logoPushButton;

//    ui->logoPushButton->setImage("Main_menu", "comlaser_logo.bmp");
//    QDir qdir;
    QPixmap pixmap;
    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "Main_menu" + "/" + "comlaser_logo.bmp");
//    qDebug() << GeteMMCPath() + "images" + "/" + "Main_menu" + "/" + "comlaser_logo.bmp";
    ui->logoPushButton->setIcon(QIcon(pixmap));
    ui->logoPushButton->setIconSize(pixmap.rect()/*.adjusted(1, 1, -1, -1)*/.size());
    ui->logoPushButton->setStyleSheet("QPushButton {border : none;} QPushButton:pressed {border: 2px solid red;}");
    ui->logoPushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainMenuContentWidget::~MainMenuContentWidget()
{
    delete ui;
}

//void MainMenuContentWidget::on_settingPushButton_clicked()
//{
//    SettingWidget settingWidget;
//    settingWidget.setGeometry(this->geometry());
//    settingWidget.exec();
//}

//void MainMenuContentWidget::on_fileManagementPushButton_clicked()
//{
//    FileManagementWidget fileManagementWidget;
//    fileManagementWidget.setGeometry(this->geometry());
//    fileManagementWidget.exec();
//}

//void MainMenuContentWidget::on_enforcementPushButton_clicked()
//{

//}
