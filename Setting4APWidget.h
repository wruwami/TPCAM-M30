/**
 * @file Setting4APWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 세팅4 AP모드 화면 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SETTING4APWIDGET_H
#define SETTING4APWIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting4APWidget;
}

/**
 * @brief 세팅4 AP모드 화면 위젯 클래스
 * 
 */
class Setting4APWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting4APWidget(QWidget *parent = 0);
    ~Setting4APWidget();
    void SaveConfig();
private slots:
    void on_pwPushButton_clicked();    
    void on_wifiSSIDnFTPlineEdit_textChanged(const QString &arg1);

    void on_ipLineEdit_textChanged(const QString &arg1);

    void on_subnetMaskLineEdit_textChanged(const QString &arg1);

    void on_printerComboBox_currentIndexChanged(int index);

private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting4.json");
//    bool m_bNetworkPassword;
//    bool m_bPasswordChanging = false;
    QString m_strNewPassword;
private:
    Ui::Setting4APWidget *ui;
protected slots:
    void on_sendPW(QString);
};

#endif // SETTING4APWIDGET_H
