#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QJsonObject>
#include <QQueue>

#include "ConfigManager.h"

class CustomPushButton;
class CustomComboBox;
class LightManager;
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
private:
//    void ItemBackPush(QString);
//    void ItemFrontPush(QString);
//    QString m_userName;
private slots:
    void on_loginPushButton_clicked();
    void on_dateTimePushButton_clicked();

    void on_lightPushButton_clicked();

    void on_userNamePushButton_clicked();

//    void on_userNameComboBox_currentIndexChanged(const QString &arg);

    void on_userNameComboBox_currentIndexChanged(int index);

public:
    CustomPushButton* m_loginPushButton;
    CustomPushButton* m_dateTimePushButton;
    CustomComboBox* m_pUserNameComboBox;
private:
    QJsonObject m_jsonObject;
    ConfigManager m_config = ConfigManager("parameter_login.json");
    LightManager* m_pLightMager = nullptr;
//    QQueue<QString> m_queue;
private:
    Ui::LoginWidget *ui;

};

#endif // LOGINWIDGET_H
