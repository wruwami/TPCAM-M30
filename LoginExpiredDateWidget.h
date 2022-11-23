#ifndef LOGINEXPIREDDATEWIDGET_H
#define LOGINEXPIREDDATEWIDGET_H

#include <QWidget>

namespace Ui {
class LoginExpiredDateWidget;
}

class LoginExpiredDateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginExpiredDateWidget(QWidget *parent = 0);
    ~LoginExpiredDateWidget();

private:
    Ui::LoginExpiredDateWidget *ui;
};

#endif // LOGINEXPIREDDATEWIDGET_H
