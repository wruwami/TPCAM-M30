#include "MainMenuAdminAlignWidget.h"
#include "ui_MainMenuAdminAlignWidget.h"

#include "StringLoader.h"

MainMenuAdminAlignWidget::MainMenuAdminAlignWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuAdminAlignWidget)
{
    ui->setupUi(this);

    m_pDeviceIdWidget = ui->deviceIDPushButton;
    m_pCameraAlignWidget = ui->cameraHUDAlignPushButton;
    m_pCameraZoomFocusWidget = ui->cameraZoomFocusPushButton;

    ui->deviceIDPushButton->setText(LoadString("IDS_DEVICE_ID"));
    ui->cameraZoomFocusPushButton->setText(LoadString("IDS_CAMERA_ZOOM_FOCUS"));
    ui->cameraHUDAlignPushButton->setText(LoadString("IDS_CAMERA_HUD_ALIGN"));

    ui->label->setImage("Main_menu", "comlaser_logo.bmp");
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
