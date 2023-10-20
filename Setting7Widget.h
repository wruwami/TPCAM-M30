#ifndef SETTING7WIDGET_H
#define SETTING7WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting7Widget;
}

class Setting7Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting7Widget(QWidget *parent = 0);
    ~Setting7Widget();
    void SaveConfig();
private slots:
    void on_wifiComboBox_currentIndexChanged(int index);

//    void on_bluetoothComboBox_currentIndexChanged(int index);

    void on_nineAxisSensorComboBox_currentIndexChanged(int index);

    void on_micnSpeackerComboBox_currentIndexChanged(int index);


    void on_powerSavingTimeComboBox_currentIndexChanged(int index);

    void on_gpsComboBox_currentIndexChanged(int index);

private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting7.json");

private:
    Ui::Setting7Widget *ui;
};

#endif // SETTING7WIDGET_H
