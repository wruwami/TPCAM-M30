#ifndef SETTING3WIDGET_H
#define SETTING3WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

namespace Ui {
class Setting3Widget;
}

class Setting3Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting3Widget(QWidget *parent = 0);
    ~Setting3Widget();

private slots:
    void on_showInfoPushButton_clicked();

    void on_factoryDefaultPushButton_clicked();

    void on_adminPWPushButton_clicked();
    void on_lcdBrightnessComboBox_currentIndexChanged(int index);

    void on_unitComboBox_currentIndexChanged(int index);

    void on_dateFormatComboBox_currentIndexChanged(int index);

public:
    bool m_isSave = false;
private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting3.json");

private:
    Ui::Setting3Widget *ui;
};

#endif // SETTING3WIDGET_H
