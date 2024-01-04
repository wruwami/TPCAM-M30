/**
 * @file Setting5Widget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 세팅5 화면 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SETTING5WIDGET_H
#define SETTING5WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting5Widget;
}

/**
 * @brief 세팅5 화면 위젯 클래스
 * 
 */
class Setting5Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting5Widget(QWidget *parent = 0);
    ~Setting5Widget();
    void SaveConfig();
    void timerEvent(QTimerEvent *event);
private:
    void setDHCPMode();
    void setManualMode();
private slots:
    void on_ipAddressComboBox_currentIndexChanged(int index);
    void on_ipLineEdit_textChanged(const QString &arg1);

    void on_subnetMaskLineEdit_textChanged(const QString &arg1);

    void on_gatewayLineEdit_textChanged(const QString &arg1);

    void on_dnsServerLineEdit_textChanged(const QString &arg1);

private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting5.json");

private:
    Ui::Setting5Widget *ui;
};

#endif // SETTING5WIDGET_H
