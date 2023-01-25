#ifndef SETTING2WIDGET_H
#define SETTING2WIDGET_H

#include <QWidget>
#include <QJsonObject>

#include "ConfigManager.h"

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
private:
    Ui::Setting2Widget *ui;
private:
    QJsonObject m_jsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting2.json");

};

#endif // SETTING2WIDGET_H
