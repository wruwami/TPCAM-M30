#ifndef ENFORCEMENTWIDGET_H
#define ENFORCEMENTWIDGET_H

#include <QWidget>
#include "EnforcementComponentWidget.h"

namespace Ui {
class EnforcementWidget;
}

class EnforcementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementWidget(QWidget *parent = 0);
    ~EnforcementWidget();
    EnforcementComponentWidget* m_pEnforcementComponentWidget = nullptr;
private:
    Ui::EnforcementWidget *ui;
};

#endif // ENFORCEMENTWIDGET_H
