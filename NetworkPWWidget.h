#ifndef NETWORKPWWIDGET_H
#define NETWORKPWWIDGET_H

#include <QWidget>

namespace Ui {
class NetworkPWWidget;
}

class NetworkPWWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkPWWidget(QWidget *parent = 0);
    ~NetworkPWWidget();

private:
    Ui::NetworkPWWidget *ui;
};

#endif // NETWORKPWWIDGET_H
