#ifndef ENFORCEMENTWARNINGMESSAGEWIDGET_H
#define ENFORCEMENTWARNINGMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class EnforcementWarningMessageWidget;
}

class EnforcementWarningMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementWarningMessageWidget(QWidget *parent = 0);
    ~EnforcementWarningMessageWidget();

private:
    Ui::EnforcementWarningMessageWidget *ui;
};

#endif // ENFORCEMENTWARNINGMESSAGEWIDGET_H
