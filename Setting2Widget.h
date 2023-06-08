#ifndef SETTING2WIDGET_H
#define SETTING2WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"
#include "HUDManager.h"

namespace Ui {
class Setting2Widget;
}

class Setting2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting2Widget(QWidget *parent = 0);
    ~Setting2Widget();
public:
    bool m_isSave = false;
private slots:
    void on_antiJammingModeComboBox_currentIndexChanged(int index);

    void on_reticleShapeComboBox_currentIndexChanged(int index);

    void on_weatherModeComboBox_currentIndexChanged(int index);

    void on_daynNightComboBox_currentIndexChanged(int index);

    void on_buzzerComboBox_currentIndexChanged(int index);

private:
    Ui::Setting2Widget *ui;
    HUDManager m_hud;
private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting2.json");

};

#endif // SETTING2WIDGET_H
