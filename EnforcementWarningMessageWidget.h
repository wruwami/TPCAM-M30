#ifndef ENFORCEMENTWARNINGMESSAGEWIDGET_H
#define ENFORCEMENTWARNINGMESSAGEWIDGET_H

#include <QDialog>

namespace Ui {
class EnforcementWarningMessageDialog;
}

class EnforcementWarningMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnforcementWarningMessageDialog(QWidget *parent = 0);
    ~EnforcementWarningMessageDialog();

private:
    Ui::EnforcementWarningMessageDialog *ui;
};

#endif // ENFORCEMENTWARNINGMESSAGEWIDGET_H
