#ifndef ENFORCEMENTCOMPONENT2WIDGET_H
#define ENFORCEMENTCOMPONENT2WIDGET_H

#include <QWidget>

namespace Ui {
class EnforcementComponent2Widget;
}

class EnforcementComponent2Widget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementComponent2Widget(QWidget *parent = 0);
    ~EnforcementComponent2Widget();

private:
    Ui::EnforcementComponent2Widget *ui;
};

#endif // ENFORCEMENTCOMPONENT2WIDGET_H
