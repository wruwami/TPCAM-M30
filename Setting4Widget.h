#ifndef SETTING4WIDGET_H
#define SETTING4WIDGET_H

#include <QWidget>

namespace Ui {
class Setting4Widget;
}

class Setting4Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting4Widget(QWidget *parent = 0);
    ~Setting4Widget();

private:
    Ui::Setting4Widget *ui;
};

#endif // SETTING4WIDGET_H
