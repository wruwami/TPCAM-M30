#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private slots:
    void on_loginPushButton_clicked();
    void on_dateTimePushButton_clicked();

    void on_lightPushButton_clicked();

public:
    CustomPushButton* m_loginPushButton;
    CustomPushButton* m_dateTimePushButton;
private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
