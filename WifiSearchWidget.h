#ifndef WIFISEARCHWIDGET_H
#define WIFISEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class WifiSearchWidget;
}

class WifiSearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WifiSearchWidget(QWidget *parent = 0);
    ~WifiSearchWidget();

private:
    Ui::WifiSearchWidget *ui;
};

#endif // WIFISEARCHWIDGET_H
