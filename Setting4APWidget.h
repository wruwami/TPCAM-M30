#ifndef SETTING4APWIDGET_H
#define SETTING4APWIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting4APWidget;
}

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

private:
    Ui::Setting4APWidget *ui;
};

#endif // SETTING4APWIDGET_H
