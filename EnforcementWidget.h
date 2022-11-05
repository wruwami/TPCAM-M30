#ifndef ENFORCEMENTWIDGET_H
#define ENFORCEMENTWIDGET_H

#include <QWidget>

namespace Ui {
class EnforcementWidget;
}

class EnforcementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementWidget(QWidget *parent = 0);
    ~EnforcementWidget();

private:
    Ui::EnforcementWidget *ui;
};

#endif // ENFORCEMENTWIDGET_H
