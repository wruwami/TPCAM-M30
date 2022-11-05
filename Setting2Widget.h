#ifndef SETTING2WIDGET_H
#define SETTING2WIDGET_H

#include <QWidget>

namespace Ui {
class Setting2Widget;
}

class Setting2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting2Widget(QWidget *parent = 0);
    ~Setting2Widget();

private:
    Ui::Setting2Widget *ui;
};

#endif // SETTING2WIDGET_H
