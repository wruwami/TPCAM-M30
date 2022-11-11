#include "Setting3Widget.h"
#include "ui_Setting3Widget.h"

#include "StringLoader.h"

Setting3Widget::Setting3Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting3Widget)
{
    ui->setupUi(this);

    ui->lcdBrightnessLabel->setText(LoadString("IDS_LCD_BRIGHTNESS"));
    ui->unitLabel->setText(LoadString("IDS_UNIT"));
    ui->dateFormatLabel->setText(LoadString("IDS_DATE_FORMAT"));
    ui->showInfoPushButton->setText(LoadString("IDS_SHOW_INFO"));
    ui->factoryDefaultPushButton->setText(LoadString("IDS_FACTORY_DEFAULT"));
    ui->adminPWPushButton->setText(LoadString("IDS_ADMIN_PW"));
}

Setting3Widget::~Setting3Widget()
{
    delete ui;
}
