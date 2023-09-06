#include "Setting7Widget.h"
#include "ui_Setting7Widget.h"

#include <QJsonArray>

#include "StringLoader.h"

Setting7Widget::Setting7Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting7Widget)
{
    ui->setupUi(this);

    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->WifiLabel->setText(LoadString("IDS_WIFI"));
    ui->WifiLabel->setFontSize(23);
    ui->blueToothLabel->setText(LoadString("IDS_BLUETOOTH"));
    ui->blueToothLabel->setFontSize(23);
    ui->nineAxisSensorLabel->setText(LoadString("IDS_NINE_AXIS_SENSOR"));
    ui->nineAxisSensorLabel->setFontSize(23);
    ui->micnSpeackerLabel->setText(LoadString("IDS_MIC_N_SPEAKER"));
    ui->micnSpeackerLabel->setFontSize(23);
    ui->powerSavingTimeLabel->setText(LoadString("IDS_POWER_SAVING_TIME"));
    ui->powerSavingTimeLabel->setFontSize(23);

//    ui->wifiComboBox->addItem(LoadString("IDS_ON"));
//    ui->wifiComboBox->addItem(LoadString("IDS_OFF"));
    foreach (QJsonValue json, m_jsonObject["wifi items"].toArray())
    {
        ui->wifiComboBox->addItem(json.toString());
    }
    int index = m_jsonObject["wifi select"].toInt();
    ui->wifiComboBox->setCurrentIndex(index - 1);


//    ui->bluetoothComboBox->addItem(LoadString("IDS_ON"));
//    ui->bluetoothComboBox->addItem(LoadString("IDS_OFF"));
    foreach (QJsonValue json, m_jsonObject["bluetooth items"].toArray())
    {
        ui->bluetoothComboBox->addItem(json.toString());
    }
    index = m_jsonObject["bluetooth select"].toInt();
    ui->bluetoothComboBox->setCurrentIndex(index - 1);


//    ui->nineAxisSensorComboBox->addItem(LoadString("IDS_ON"));
//    ui->nineAxisSensorComboBox->addItem(LoadString("IDS_OFF"));
    foreach (QJsonValue json, m_jsonObject["9 axis items"].toArray())
    {
        ui->nineAxisSensorComboBox->addItem(json.toString());
    }
    index = m_jsonObject["9 axis select"].toInt();
    ui->nineAxisSensorComboBox->setCurrentIndex(index - 1);


//    ui->micnSpeackerComboBox->addItem(LoadString("IDS_ON"));
//    ui->micnSpeackerComboBox->addItem(LoadString("IDS_OFF"));
    foreach (QJsonValue json, m_jsonObject["mic_speaker items"].toArray())
    {
        ui->micnSpeackerComboBox->addItem(json.toString());
    }
    index = m_jsonObject["mic_speaker select"].toInt();
    ui->micnSpeackerComboBox->setCurrentIndex(index - 1);


//    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_OFF"));
//    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_10_MINUTE"));
//    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_20_MINUTE"));
//    ui->powerSavingTimeComboBox->addItem(LoadString("IDS_30_MINUTE"));
//    ui->powerSavingTimeComboBox->setCurrentIndex(2);
    foreach (QJsonValue json, m_jsonObject["power saving items"].toArray())
    {
        ui->powerSavingTimeComboBox->addItem(json.toString());
    }
    index = m_jsonObject["power saving select"].toInt();
    ui->powerSavingTimeComboBox->setCurrentIndex(index - 1);

}

Setting7Widget::~Setting7Widget()
{
    delete ui;
}

void Setting7Widget::SaveConfig()
{
    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();

}

void Setting7Widget::on_wifiComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["wifi select"] = index + 1;
}

void Setting7Widget::on_bluetoothComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["bluetooth select"] = index + 1;
}

void Setting7Widget::on_nineAxisSensorComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["9 axis select"] = index + 1;
}

void Setting7Widget::on_micnSpeackerComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["mic_speaker select"] = index + 1;
}

void Setting7Widget::on_powerSavingTimeComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["power saving select"] = index + 1;
}
