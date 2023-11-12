#ifndef SETTING4STAWIDGET_H
#define SETTING4STAWIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting4STAWidget;
}

class Setting4STAWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting4STAWidget(QWidget *parent = 0);
    ~Setting4STAWidget();
    void SaveConfig();
private:
    int CheckComboxBoxItem(QString);
private slots:
    void on_pwPushButton_clicked();
    void on_FTPIDPWLineEdit_textChanged(const QString &arg1);

    void on_ipLineEdit_textChanged(const QString &arg1);

    void on_subnetMaskLineEdit_textChanged(const QString &arg1);

    void on_printerComboBox_currentIndexChanged(int index);

    void on_searchPushButton_clicked();

    void on_wifiSSIDComboBox_currentIndexChanged(int index);

private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    QJsonObject m_passwordjsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting4.json");
    ConfigManager m_config2 = ConfigManager("setting_password.json");
    int m_nSSIDIndex = 0;
    bool m_bSearching = false;
    QString m_strNewPassword;
protected slots:
    void on_sendSSID(QString);
    void on_sendPW(QString);
private:
    Ui::Setting4STAWidget *ui;
};

#endif // SETTING4STAWIDGET_H
