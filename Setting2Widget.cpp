#include "Setting2Widget.h"
#include "ui_Setting2Widget.h"

#include <QJsonArray>

#include "StringLoader.h"

Setting2Widget::Setting2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting2Widget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;


    ui->reticleShapeLabel->setText(LoadString("IDS_RETICLE_SHAPE"));
    ui->reticleShapeLabel->setFontSize(23);
    ui->weatherModeLabel->setText(LoadString("IDS_WEATHER_MODE"));
    ui->weatherModeLabel->setFontSize(23);
    ui->daynNightLabel->setText(LoadString("IDS_DAYNIGHT"));
    ui->daynNightLabel->setFontSize(23);
    ui->buzzerLabel->setText(LoadString("IDS_BUZZER"));
    ui->buzzerLabel->setFontSize(23);
    ui->antiJammingModeLabel->setText(LoadString("IDS_ANTI_JAMMING_MODE"));
    ui->antiJammingModeLabel->setFontSize(23);

//    ui->reticleShapeComboBox->addItem(LoadString("IDS_CROSS"));
//    ui->reticleShapeComboBox->addItem(LoadString("IDS_DOT"));
//    ui->reticleShapeComboBox->addItem(LoadString("IDS_ROUND"));
//    ui->reticleShapeComboBox->addItem(LoadString("IDS_RECTANGLE"));
    foreach (QJsonValue json, m_jsonObject["reticle items"].toArray())
    {
        ui->reticleShapeComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    int index = m_jsonObject["reticle selection"].toInt() - 1;
    ui->reticleShapeComboBox->setCurrentIndex(index);

//    ui->weatherModeComboBox->addItem(LoadString("IDS_SUNNY"));
    foreach (QJsonValue json, m_jsonObject["weather mode items"].toArray())
    {
        ui->weatherModeComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["weather selection"].toInt() - 1;
    ui->weatherModeComboBox->setCurrentIndex(index);


//    ui->daynNightComboBox->addItem(LoadString("IDS_DAY_DARK"));
//    ui->daynNightComboBox->addItem(LoadString("IDS_DAY_STANDARD"));
//    ui->daynNightComboBox->addItem(LoadString("IDS_DAY_BRIGHT"));
//    ui->daynNightComboBox->addItem(LoadString("IDS_NIGHT_DARK"));
//    ui->daynNightComboBox->addItem(LoadString("IDS_NIGHT_STANDARD"));
//    ui->daynNightComboBox->addItem(LoadString("IDS_NIGHT_BRIGHT"));
    foreach (QJsonValue json, m_jsonObject["day&night mode items"].toArray())
    {
        ui->daynNightComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["day&night selection"].toInt() - 1;
    ui->daynNightComboBox->setCurrentIndex(index);

//    ui->buzzerComboBox->addItem(LoadString("IDS_ON"));
//    ui->buzzerComboBox->addItem(LoadString("IDS_OFF"));
    foreach (QJsonValue json, m_jsonObject["buzzer items"].toArray())
    {
        ui->buzzerComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["buzzer selection"].toInt() - 1;
    ui->buzzerComboBox->setCurrentIndex(index);

//    ui->antiJammingModeComboBox->addItem(LoadString("IDS_ON"));
//    ui->antiJammingModeComboBox->addItem(LoadString("IDS_OFF"));
    foreach (QJsonValue json, m_jsonObject["anti-jamming items"].toArray())
    {
        ui->antiJammingModeComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    index = m_jsonObject["anti-jamming selection"].toInt() - 1;
    ui->antiJammingModeComboBox->setCurrentIndex(index);

}

Setting2Widget::~Setting2Widget()
{
   delete ui;
}

void Setting2Widget::SaveConfig()
{
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

//    SerialLaserManager laserManager;
//    laserManager.set_weather_mode(m_newJsonObject["weather selection"].toInt());

//    ViscaManager viscaManager;
//    viscaManager.SetDayMode(m_newJsonObject["day&night selection"].toInt());
}

void Setting2Widget::on_antiJammingModeComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["anti-jamming selection"] = index + 1;
}

void Setting2Widget::on_reticleShapeComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["reticle selection"] = index + 1;
}

void Setting2Widget::on_weatherModeComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["weather selection"] = index + 1;
}

void Setting2Widget::on_daynNightComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["day&night selection"] = index + 1;
}

void Setting2Widget::on_buzzerComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["buzzer selection"] = index + 1;
}
