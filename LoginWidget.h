#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QJsonObject>
#include "ConfigManager.h"

class CustomPushButton;
class CustomComboBox;
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
public:
//    QString m_userName;
private slots:
    void on_loginPushButton_clicked();
    void on_dateTimePushButton_clicked();

    void on_lightPushButton_clicked();

    void on_userNamePushButton_clicked();

//    void on_userNameComboBox_currentIndexChanged(const QString &arg);

public:
    CustomPushButton* m_loginPushButton;
    CustomPushButton* m_dateTimePushButton;
    CustomComboBox* m_pUserNameComboBox;
private:
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("parameter_login.json");
private:
    Ui::LoginWidget *ui;

};

#endif // LOGINWIDGET_H
