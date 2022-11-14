#ifndef INDICATORCAMERAWIDGET_H
#define INDICATORCAMERAWIDGET_H

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

#endif // INDICATORCAMERAWIDGET_H
