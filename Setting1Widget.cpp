#include "Setting1Widget.h"
#include "ui_Setting1Widget.h"

#include "StringLoader.h"
#include "BaseDialog.h"

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

    ui->locationPushButton->setImage("setting_1", "keyboard.bmp");

    ui->speedLimit1LineEdit->setText("100");
    ui->speedLimit2LineEdit->setText("80");
    ui->speedLimit3LineEdit->setText("60");
    ui->captureSpeedLimit1LineEdit->setText("110");
    ui->captureSpeedLimit2LineEdit->setText("90");
    ui->captureSpeedLimit3LineEdit->setText("70");

    ui->speedLimit1LineEdit->SetMode(KeypadType);
    ui->speedLimit2LineEdit->SetMode(KeypadType);
    ui->speedLimit3LineEdit->SetMode(KeypadType);
    ui->captureSpeedLimit1LineEdit->SetMode(KeypadType);
    ui->captureSpeedLimit2LineEdit->SetMode(KeypadType);
    ui->captureSpeedLimit3LineEdit->SetMode(KeypadType);
}

Setting1Widget::~Setting1Widget()
{
    delete ui;
}


void Setting1Widget::on_locationPushButton_clicked()
{
    BaseDialog baseDialog(Setting1LocationWidgetType, Qt::AlignmentFlag::AlignCenter, "", true);
    baseDialog.exec();
}
