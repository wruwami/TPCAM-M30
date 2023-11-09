#include "Setting3Widget.h"
#include "ui_Setting3Widget.h"

#include <QJsonArray>
#include "StringLoader.h"

#include "BaseDialog.h"
#include "SpeedUnitManager.h"

#include "CustomPushButton.h"
#include "FactoryDefaultWidget.h"
#include "PasswordChangingWidget.h"
#include "DateFormatManager.h"

Setting3Widget::Setting3Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting3Widget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->lcdBrightnessLabel->setText(LoadString("IDS_LCD_BRIGHTNESS"));
    ui->lcdBrightnessLabel->setFontSize(23);
    ui->unitLabel->setText(LoadString("IDS_UNIT"));
    ui->unitLabel->setFontSize(23);
    ui->dateFormatLabel->setText(LoadString("IDS_DATE_FORMAT"));
    ui->dateFormatLabel->setFontSize(23);
    ui->showInfoPushButton->setText(LoadString("IDS_SHOW_INFO"));
    ui->showInfoPushButton->setFontSize(23);
    ui->factoryDefaultPushButton->setText(LoadString("IDS_FACTORY_DEFAULT"));
    ui->factoryDefaultPushButton->setFontSize(23);
    ui->adminPWPushButton->setText(LoadString("IDS_ADMIN_PW"));
    ui->adminPWPushButton->setFontSize(23);

//    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL1"));
//    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL2"));
//    ui->lcdBrightnessComboBox->addItem(LoadString("IDS_LEVEL3"));
    foreach (QJsonValue json, m_jsonObject["lcd brightness items"].toArray())
    {
        ui->lcdBrightnessComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    int index = m_jsonObject["lcd brightness selection"].toInt() - 1;
    ui->lcdBrightnessComboBox->setCurrentIndex(index);


//    ui->unitComboBox->addItem(LoadString("IDS_KM_PER_H"));
//    ui->unitComboBox->addItem(LoadString("IDS_MPH_FT"));
//    ui->unitComboBox->setCurrentIndex(0);
    foreach (QJsonValue json, m_jsonObject["unit items"].toArray())
    {
        ui->unitComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["unit selection"].toInt() - 1;
    ui->unitComboBox->setCurrentIndex(index);



//    ui->dateFormatComboBox->addItem(LoadString("IDS_YYYY_MM_DD"));
//    ui->dateFormatComboBox->addItem(LoadString("IDS_MM_DD_YYYY"));
//    ui->dateFormatComboBox->addItem(LoadString("IDS_DD_MM_YYYY"));
//    ui->dateFormatComboBox->setCurrentIndex(0);
    foreach (QJsonValue json, m_jsonObject["date format items"].toArray())
    {
        ui->dateFormatComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["date format selection"].toInt() - 1;
    ui->dateFormatComboBox->setCurrentIndex(index);

    m_pSystemInfoButton = ui->showInfoPushButton;
}

Setting3Widget::~Setting3Widget()
{
    delete ui;
}

void Setting3Widget::SaveConfig()
{
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

    if (m_newJsonObject["unit selection"].toInt() == 1)
    {
        SpeedUnitManager::GetInstance()->setSpeedUnit(Km);
        SpeedUnitManager::GetInstance()->setDistance(meter);
    }
    else
    {
        SpeedUnitManager::GetInstance()->setSpeedUnit(mile);
        SpeedUnitManager::GetInstance()->setDistance(feet);
    }
    switch (m_newJsonObject["date format selection"].toInt() - 1)
    {
    case 0:
    {
        SetDateFormat(YYYYMMDD);
    }
        break;
    case 1:
    {
        SetDateFormat(MMDDYYYY);
    }
        break;
    case 2:
    {
        SetDateFormat(DDMMYYYY);
    }
        break;

    }
}

void Setting3Widget::on_showInfoPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::Setting3SystemInfoWidgetType,Qt::AlignmentFlag::AlignCenter, "", true);
    baseDialog.exec();
}

void Setting3Widget::on_factoryDefaultPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::Setting3FactoryDefaultWidgetType, Qt::AlignmentFlag::AlignCenter, LoadString("IDS_ARE_U_SURE_FACTORY_DEFAULT"));
    if (baseDialog.exec() == QDialog::Accepted)
    {
        FactoryDefaultWidget factoryDefaultWidget;
        factoryDefaultWidget.MoveFactorySetting();
    }
}

void Setting3Widget::on_adminPWPushButton_clicked()
{
    BaseDialog baseDialog(Dialog::AdminPWWidgetType, Qt::AlignmentFlag::AlignCenter, LoadString("IDS_PLEASE_INPUT_PW"));
    if (baseDialog.exec() == QDialog::Accepted)
    {
        BaseDialog baseDialog(Dialog::PasswordChangingWidgetType, Qt::AlignmentFlag::AlignCenter, "");
        connect((PasswordChangingWidget*)baseDialog.pWidget(), SIGNAL(sig_sendPW(QString)), this, SLOT(on_sendPW(QString)));
        if (baseDialog.exec() == QDialog::Accepted)
        {
            ConfigManager config = ConfigManager("setting_password.json");
            QJsonObject object = config.GetConfig();
            object["password"] = m_strNewPassword;
            config.SetConfig(object);
            config.SaveFile();
        }
    }
}

void Setting3Widget::on_lcdBrightnessComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["lcd brightness selection"] = index + 1;
}

void Setting3Widget::on_unitComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["unit selection"] = index + 1;
}

void Setting3Widget::on_dateFormatComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["date format selection"] = index + 1;
}

void Setting3Widget::on_sendPW(QString str)
{
    m_strNewPassword = str;
}

