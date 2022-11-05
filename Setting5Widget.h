#ifndef SETTING5WIDGET_H
#define SETTING5WIDGET_H

#include <QWidget>

namespace Ui {
class Setting5Widget;
}

class Setting5Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting5Widget(QWidget *parent = 0);
    ~Setting5Widget();

private:
    Ui::Setting5Widget *ui;
};

#endif // SETTING5WIDGET_H
