#include "MainMenuAdminAlignWidget.h"
#include "ui_MainMenuAdminAlignWidget.h"

#include "qdir.h"

#include "StringLoader.h"
#include "Color.h"
#include "FileManager.h"

MainMenuAdminAlignWidget::MainMenuAdminAlignWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuAdminAlignWidget)
{
    ui->setupUi(this);

    setBackGroundColor(this, 0xffffff);

    m_pDeviceIdWidget = ui->deviceIDPushButton;
    m_pCameraAlignWidget = ui->cameraHUDAlignPushButton;
    m_pCameraZoomFocusWidget = ui->cameraZoomFocusPushButton;

    ui->deviceIDPushButton->setText(LoadString("IDS_DEVICE_ID"));
    ui->deviceIDPushButton->setFontSize(23);
    ui->cameraZoomFocusPushButton->setText(LoadString("IDS_CAMERA_ZOOM_FOCUS"));
    ui->cameraZoomFocusPushButton->setFontSize(23);
    ui->cameraHUDAlignPushButton->setText(LoadString("IDS_CAMERA_HUD_ALIGN"));
    ui->cameraHUDAlignPushButton->setFontSize(23);

    QString style = "background-color : #f9d979; border = 5px solid #385d8a;";
    ui->deviceIDPushButton->setStyleSheet(style);
    ui->cameraZoomFocusPushButton->setStyleSheet(style);
    ui->cameraHUDAlignPushButton->setStyleSheet(style);

    m_pLogoButton = ui->logoPushButton;

//    ui->logoPushButton->setImage("Main_menu", "comlaser_logo.bmp");
    QDir qdir;
    QPixmap pixmap;
    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "Main_menu" + "/" + "comlaser_logo.bmp");
    ui->logoPushButton->setIcon(QIcon(pixmap));
    ui->logoPushButton->setIconSize(pixmap.rect().adjusted(1, -1, -1, 1).size());
//    QFile file(":/style/customPushButton.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = QString::fromLatin1(file.readAll());
//    file.close();
//    ui->logoPushButton->setStyleSheet(styleSheet);
}

MainMenuAdminAlignWidget::~MainMenuAdminAlignWidget()
{
    delete ui;
}

//void MainMenuAdminAlignWidget::on_deviceIDPushButton_clicked()
//{

//}

//void MainMenuAdminAlignWidget::on_cameraHUDAlignPushButton_clicked()
//{

//}

//void MainMenuAdminAlignWidget::on_cameraZoomFocusPushButton_clicked()
//{

//}
