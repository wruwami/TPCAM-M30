#ifndef SETTING5WIDGET_H
#define SETTING5WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting5Widget;
}

class Setting5Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting5Widget(QWidget *parent = 0);
    ~Setting5Widget();
private:
    void setDHCPMode();
    void setManualMode();
private slots:
    void on_ipAddressComboBox_currentIndexChanged(int index);
private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting5.json");

private:
    Ui::Setting5Widget *ui;
};

#endif // SETTING5WIDGET_H
