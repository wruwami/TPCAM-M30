#ifndef SETTING1WIDGET_H
#define SETTING1WIDGET_H

#include <QWidget>

namespace Ui {
class Setting1Widget;
}

class Setting1Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting1Widget(QWidget *parent = 0);
    ~Setting1Widget();

private slots:
    void on_locationPushButton_clicked();

private:
    Ui::Setting1Widget *ui;
};

#endif // SETTING1WIDGET_H
