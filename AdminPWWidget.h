#ifndef ADMINPWWIDGET_H
#define ADMINPWWIDGET_H

#include <QWidget>

namespace Ui {
class AdminPWWidget;
}

class AdminPWWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPWWidget(QWidget *parent = 0);
    ~AdminPWWidget();

private:
    Ui::AdminPWWidget *ui;
};

#endif // ADMINPWWIDGET_H
