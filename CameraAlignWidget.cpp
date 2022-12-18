#include "CameraAlignWidget.h"
#include "ui_CameraAlignWidget.h"

#include "StringLoader.h"

#include "CustomPushButton.h"

CameraAlignWidget::CameraAlignWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAlignWidget)
{
    ui->setupUi(this);

    ui->homePushButton->setText(LoadString("IDS_HOME"));
    ui->defaultPushButton->setText(LoadString("IDS_DEFAULT"));
    ui->autoTriggerPushButton->setText(LoadString("IDS_AUTO_TRIGGER"));
    ui->hudPushButton->setText(LoadString("IDS_HUD"));
    ui->upPushButton->setText(LoadString("IDS_UP"));
    ui->leftPushButton->setText(LoadString("IDS_LEFT"));
    ui->rightPushButton->setText(LoadString("IDS_RIGHT"));
    ui->downPushButton->setText(LoadString("IDS_DOWN"));
    ui->savePushButton->setText(LoadString("IDS_SAVE"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cameraPushButton->setText(LoadString("IDS_CAMERA"));

    m_pHomeButton = ui->homePushButton;
}

CameraAlignWidget::~CameraAlignWidget()
{
    delete ui;
}
