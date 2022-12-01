#include "Setting3Widget.h"
#include "ui_Setting3Widget.h"

#include "StringLoader.h"

#include "BaseDialog.h"

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

    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL1"));
    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL2"));
    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL3"));

    ui->unitComboBox->addItem(LoadString("IDS_KM_PER_H"));
    ui->unitComboBox->addItem(LoadString("IDS_MPH_FT"));
    ui->unitComboBox->setCurrentIndex(0);

    ui->unitComboBox->addItem(LoadString("IDS_YYYY_MM_DD"));
    ui->unitComboBox->addItem(LoadString("IDS_MM_DD_YYYY"));
    ui->unitComboBox->addItem(LoadString("IDS_DD_MM_YYYY"));
    ui->unitComboBox->setCurrentIndex(0);
}

Setting3Widget::~Setting3Widget()
{
    delete ui;
}

void Setting3Widget::on_showInfoPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::Setting3SystemInfoWidgetType);
    baseDialog.exec();
}

void Setting3Widget::on_factoryDefaultPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::Setting3FactoryDefaultWidgetType);
    baseDialog.exec();
}

void Setting3Widget::on_adminPWPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::AdminPWWidgetType);
    baseDialog.exec();
}
