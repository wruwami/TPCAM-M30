#include "Setting1Widget.h"
#include "ui_Setting1Widget.h"

#include "StringLoader.h"

Setting1Widget::Setting1Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting1Widget)
{
    ui->setupUi(this);

    ui->locationLabel->setText(LoadString("IDS_LOCATION"));
    ui->speedLimitLabel->setText(LoadString("IDS_SPEED_LIMIT"));
    ui->captureSpeedLimitLabel->setText(LoadString("IDS_CAPTURE_LIMIT"));
    ui->enforcementModeLabel->setText(LoadString("IDS_ENFORCEMENT_MODE"));
    ui->speedModeLabel->setText(LoadString("IDS_SPEED_MODE"));

    ui->locationPushButton->setImage("setting_1", "keyboard.bmp");

    ui->enforcementModeComboBox->addItem(LoadString("IDS_ALL_IMAGE_VIDEO"));
    ui->enforcementModeComboBox->addItem(LoadString("IDS_AUTO_IMAGE"));
    ui->enforcementModeComboBox->addItem(LoadString("IDS_VIDEO"));

    ui->speedModeComboBox->addItem(LoadString("IDS_LT"));
    ui->speedModeComboBox->addItem(LoadString("IDS_ST"));

    ui->locationPushButton->setImage("setting1_1", "keyboard.bmp");
}

Setting1Widget::~Setting1Widget()
{
    delete ui;
}

