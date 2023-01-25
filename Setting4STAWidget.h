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

private slots:
    void on_searchPushButton_clicked();

    void on_pwPushButton_clicked();
private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_setting4.json");

private:
    Ui::Setting4STAWidget *ui;
};

#endif // SETTING4STAWIDGET_H
