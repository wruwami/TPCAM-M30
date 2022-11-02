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
public:
    CustomPushButton* m_loginPushButton;
private:
    Ui::LoginWidget *ui;
    QWidget* m_parent;
};

#endif // LOGINWIDGET_H
