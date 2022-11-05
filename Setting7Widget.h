#ifndef SETTING7WIDGET_H
#define SETTING7WIDGET_H

#include <QWidget>

namespace Ui {
class Setting7Widget;
}

class Setting7Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting7Widget(QWidget *parent = 0);
    ~Setting7Widget();

private:
    Ui::Setting7Widget *ui;
};

#endif // SETTING7WIDGET_H
