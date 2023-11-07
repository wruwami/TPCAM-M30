#include "Setting1Widget.h"
#include "ui_Setting1Widget.h"

#include <QDebug>
#include <QJsonArray>

#include "StringLoader.h"
#include "BaseDialog.h"
#include "KeyboardDialog.h"

extern int g_nCrackDownIndex;

Setting1Widget::Setting1Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting1Widget)
{
    ui->setupUi(this);

//    m_config = new ConfigManager("parameter_setting1.json");
    m_jsonObject = m_config.GetConfig();
    m_newJsonObject = m_jsonObject;

    ui->locationLabel->setText(LoadString("IDS_LOCATION"));
    ui->locationLabel->setFontSize(23);
    ui->speedLimitLabel->setText(LoadString("IDS_SPEED_LIMIT"));
    ui->speedLimitLabel->setFontSize(23);
    ui->captureSpeedLimitLabel->setText(LoadString("IDS_CAPTURE_LIMIT"));
    ui->captureSpeedLimitLabel->setFontSize(23);
    ui->enforcementModeLabel->setText(LoadString("IDS_ENFORCEMENT_MODE"));
    ui->enforcementModeLabel->setFontSize(23);
    ui->speedModeLabel->setText(LoadString("IDS_SPEED_MODE"));
    ui->speedModeLabel->setFontSize(23);

    ui->locationPushButton->setImage("setting_1", "keyboard.bmp");

//    ui->enforcementModeComboBox->addItem(LoadString("IDS_ALL_IMAGE_VIDEO"));
//    ui->enforcementModeComboBox->addItem(LoadString("IDS_AUTO_IMAGE"));
//    ui->enforcementModeComboBox->addItem(LoadString("IDS_VIDEO"));
    foreach (QJsonValue json, m_jsonObject["enforcement mode items"].toArray())
    {
        ui->enforcementModeComboBox->addItem(LoadString(json.toString().toStdString()));
    }
    int index = m_jsonObject["enforcement selection"].toInt();
    ui->enforcementModeComboBox->setCurrentIndex(index - 1);

    foreach (QJsonValue json, m_jsonObject["speed mode items"].toArray())
    {
        ui->speedModeComboBox->addItem(json.toString());
    }
    index = m_jsonObject["speed selection"].toInt();
    ui->speedModeComboBox->setCurrentIndex(index - 1);

//    ui->speedModeComboBox->addItem(LoadString("IDS_LT"));
//    ui->speedModeComboBox->addItem(LoadString("IDS_ST"));

    ui->locationPushButton->setImage("setting_1", "keyboard.bmp");

//    ui->speedLimit1LineEdit->setText("100");
//    ui->speedLimit2LineEdit->setText("80");
//    ui->speedLimit3LineEdit->setText("60");
//    ui->captureSpeedLimit1LineEdit->setText("110");
//    ui->captureSpeedLimit2LineEdit->setText("90");
//    ui->captureSpeedLimit3LineEdit->setText("70");
    ui->speedLimit1LineEdit->setText(QString::number(m_jsonObject["speed limit"].toArray()[0].toInt()));
    ui->speedLimit1LineEdit->setFontSize(23);
    ui->speedLimit2LineEdit->setText(QString::number(m_jsonObject["speed limit"].toArray()[1].toInt()));
    ui->speedLimit2LineEdit->setFontSize(23);
    ui->speedLimit3LineEdit->setText(QString::number(m_jsonObject["speed limit"].toArray()[2].toInt()));
    ui->speedLimit3LineEdit->setFontSize(23);
    ui->captureSpeedLimit1LineEdit->setText(QString::number(m_jsonObject["capture speed"].toArray()[0].toInt()));
    ui->captureSpeedLimit1LineEdit->setFontSize(23);
    ui->captureSpeedLimit2LineEdit->setText(QString::number(m_jsonObject["capture speed"].toArray()[1].toInt()));
    ui->captureSpeedLimit2LineEdit->setFontSize(23);
    ui->captureSpeedLimit3LineEdit->setText(QString::number(m_jsonObject["capture speed"].toArray()[2].toInt()));
    ui->captureSpeedLimit3LineEdit->setFontSize(23);


    ui->speedLimit1LineEdit->SetMode(KeypadType);
    ui->speedLimit2LineEdit->SetMode(KeypadType);
    ui->speedLimit3LineEdit->SetMode(KeypadType);
    ui->captureSpeedLimit1LineEdit->SetMode(KeypadType);
    ui->captureSpeedLimit2LineEdit->SetMode(KeypadType);
    ui->captureSpeedLimit3LineEdit->SetMode(KeypadType);

    foreach (QJsonValue json, m_jsonObject["location items"].toArray())
    {
        ui->locationComboBox->addItem(json.toString());
    }

    index = m_jsonObject["location selection"].toInt();
    ui->locationComboBox->setCurrentIndex(index - 1);

}

Setting1Widget::~Setting1Widget()
{
    delete ui;
}

void Setting1Widget::SaveConfig()
{
    QJsonArray ar = m_jsonObject["location items"].toArray();
    QJsonValue jv = ar[m_nLocationIndex];
    ar.removeAt(m_nLocationIndex);
    ar.insert(0, jv);
    m_newJsonObject["location selection"] = 1;
    m_newJsonObject["location items"] = ar;

    if (m_newJsonObject["enforcement selection"].toInt() != m_jsonObject["enforcement selection"].toInt())
        g_nCrackDownIndex = 1;

    m_config.SetConfig(m_newJsonObject);
    m_config.SaveFile();
}

void Setting1Widget::on_locationPushButton_clicked()
{
//    BaseDialog baseDialog(Setting1LocationWidgetType, Qt::AlignmentFlag::AlignCenter, "", true);
//    baseDialog.exec();
    KeyboardDialog keyboardDialog(GetLanguage());
    if (keyboardDialog.exec() == QDialog::Accepted)
    {
        int index = -1;
        if ((index = CheckComboxBoxItem(keyboardDialog.str())) == -1)
        {
            ui->locationComboBox->removeItem(4);
            ui->locationComboBox->insertItem(0, keyboardDialog.str());
        }
        else
        {
            ui->locationComboBox->removeItem(index);
            ui->locationComboBox->insertItem(0, keyboardDialog.str());
        }
    }

    QJsonArray array = m_jsonObject["location items"].toArray();
    while(array.count()) {
        array.pop_back();
    }
    for (int i = 0 ; i < ui->locationComboBox->count() ; i++)
    {
        array.push_back(ui->locationComboBox->itemText(i));
    }
    m_jsonObject["location items"] = array;
    m_newJsonObject["location items"] = m_jsonObject["location items"];

    ui->locationComboBox->setCurrentIndex(0);
}

void Setting1Widget::on_speedLimit1LineEdit_textChanged(const QString &arg1)
{
    QJsonArray ja;
    ja.append(arg1.toInt());
    ja.append(m_newJsonObject["speed limit"].toArray()[1]);
    ja.append(m_newJsonObject["speed limit"].toArray()[2]);

    m_newJsonObject["speed limit"] = ja;
}

void Setting1Widget::on_speedLimit2LineEdit_textChanged(const QString &arg1)
{
    QJsonArray ja;

    ja.append(m_newJsonObject["speed limit"].toArray()[0]);
    ja.append(arg1.toInt());
    ja.append(m_newJsonObject["speed limit"].toArray()[2]);

    m_newJsonObject["speed limit"] = ja;
}

void Setting1Widget::on_speedLimit3LineEdit_textChanged(const QString &arg1)
{
    QJsonArray ja;

    ja.append(m_newJsonObject["speed limit"].toArray()[0]);
    ja.append(m_newJsonObject["speed limit"].toArray()[1]);
    ja.append(arg1.toInt());

    m_newJsonObject["speed limit"] = ja;
}

void Setting1Widget::on_captureSpeedLimit1LineEdit_textChanged(const QString &arg1)
{
    QJsonArray ja;
    ja.append(arg1.toInt());
    ja.append(m_newJsonObject["capture speed"].toArray()[1]);
    ja.append(m_newJsonObject["capture speed"].toArray()[2]);

    m_newJsonObject["capture speed"] = ja;

}

void Setting1Widget::on_captureSpeedLimit2LineEdit_textChanged(const QString &arg1)
{
    QJsonArray ja;
    ja.append(m_newJsonObject["capture speed"].toArray()[0]);
    ja.append(arg1.toInt());
    ja.append(m_newJsonObject["capture speed"].toArray()[2]);

    m_newJsonObject["capture speed"] = ja;

}

void Setting1Widget::on_captureSpeedLimit3LineEdit_textChanged(const QString &arg1)
{
    QJsonArray ja;

    ja.append(m_newJsonObject["capture speed"].toArray()[0]);
    ja.append(m_newJsonObject["capture speed"].toArray()[1]);
    ja.append(arg1.toInt());

    m_newJsonObject["capture speed"] = ja;

}

void Setting1Widget::on_locationComboBox_currentIndexChanged(int index)
{
    m_nLocationIndex = index;
}

void Setting1Widget::on_enforcementModeComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["enforcement selection"] = index + 1;
}

void Setting1Widget::on_speedModeComboBox_currentIndexChanged(int index)
{
    m_newJsonObject["speed selection"] = index + 1;
}

int Setting1Widget::CheckComboxBoxItem(QString str)
{
    for (int i = 0 ; i < ui->locationComboBox->count() ; i++)
    {
        qDebug() << ui->locationComboBox->itemText(i);
        if ( str  == ui->locationComboBox->itemText(i))
            return i;
    }

    return -1;
//    foreach(auto item, ui->userNameComboBox)
//    {

//    }
}
