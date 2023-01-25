#include "Setting3Widget.h"
#include "ui_Setting3Widget.h"

#include <QJsonArray>
#include "StringLoader.h"

#include "BaseDialog.h"

Setting3Widget::Setting3Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting3Widget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->lcdBrightnessLabel->setText(LoadString("IDS_LCD_BRIGHTNESS"));
    ui->unitLabel->setText(LoadString("IDS_UNIT"));
    ui->dateFormatLabel->setText(LoadString("IDS_DATE_FORMAT"));
    ui->showInfoPushButton->setText(LoadString("IDS_SHOW_INFO"));
    ui->factoryDefaultPushButton->setText(LoadString("IDS_FACTORY_DEFAULT"));
    ui->adminPWPushButton->setText(LoadString("IDS_ADMIN_PW"));

//    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL1"));
//    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL2"));
//    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL3"));
    foreach (QJsonValue json, m_jsonObject["lcd brightness items"].toArray())
    {
        ui->lcdBrightnessComboBox->addItem(json.toString());
    }
    int index = m_jsonObject["lcd brightness selection"].toInt() - 1;
    ui->lcdBrightnessComboBox->setCurrentIndex(index);


//    ui->unitComboBox->addItem(LoadString("IDS_KM_PER_H"));
//    ui->unitComboBox->addItem(LoadString("IDS_MPH_FT"));
//    ui->unitComboBox->setCurrentIndex(0);
    foreach (QJsonValue json, m_jsonObject["unit items"].toArray())
    {
        ui->unitComboBox->addItem(json.toString());
    }
    index = m_jsonObject["unit selection"].toInt() - 1;
    ui->unitComboBox->setCurrentIndex(index);



//    ui->dateFormatComboBox->addItem(LoadString("IDS_YYYY_MM_DD"));
//    ui->dateFormatComboBox->addItem(LoadString("IDS_MM_DD_YYYY"));
//    ui->dateFormatComboBox->addItem(LoadString("IDS_DD_MM_YYYY"));
//    ui->dateFormatComboBox->setCurrentIndex(0);
    foreach (QJsonValue json, m_jsonObject["date format items"].toArray())
    {
        ui->dateFormatComboBox->addItem(json.toString());
    }
    index = m_jsonObject["date format selection"].toInt() - 1;
    ui->dateFormatComboBox->setCurrentIndex(index);


}

Setting3Widget::~Setting3Widget()
{
    delete ui;
}

void Setting3Widget::on_showInfoPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::Setting3SystemInfoWidgetType,Qt::AlignmentFlag::AlignCenter, "", true);
    baseDialog.exec();
}

void Setting3Widget::on_factoryDefaultPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::Setting3FactoryDefaultWidgetType, Qt::AlignmentFlag::AlignLeft, LoadString("IDS_ARE_U_SURE_FACTORY_DEFAULT"));
    baseDialog.exec();
}

void Setting3Widget::on_adminPWPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::AdminPWWidgetType, Qt::AlignmentFlag::AlignLeft, LoadString("IDS_PLEASE_INPUT_PW"));
    if (baseDialog.exec() == QDialog::Accepted)
    {
        BaseDialog baseDialog(Dialog::PasswordChangingWidgetType, Qt::AlignmentFlag::AlignCenter);
        baseDialog.exec();
    }
}
