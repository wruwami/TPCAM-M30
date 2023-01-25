#ifndef SETTING1WIDGET_H
#define SETTING1WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting1Widget;
}

class Setting1Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting1Widget(QWidget *parent = 0);
    ~Setting1Widget();

private slots:
    void on_locationPushButton_clicked();

    void on_speedLimit1LineEdit_textChanged(const QString &arg1);

    void on_speedLimit2LineEdit_textChanged(const QString &arg1);

    void on_speedLimit3LineEdit_textChanged(const QString &arg1);

    void on_captureSpeedLimit1LineEdit_textChanged(const QString &arg1);

    void on_captureSpeedLimit2LineEdit_textChanged(const QString &arg1);

    void on_captureSpeedLimit3LineEdit_textChanged(const QString &arg1);
    void on_locationComboBox_currentIndexChanged(int index);

    void on_enforcementModeComboBox_currentIndexChanged(int index);

    void on_speedModeComboBox_currentIndexChanged(int index);

public:
    bool m_isSave = false;
private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting1.json");
private:
    Ui::Setting1Widget *ui;
};

#endif // SETTING1WIDGET_H
