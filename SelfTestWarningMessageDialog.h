#ifndef SELFTESTWARNINGMESSAGEDIALOG_H
#define SELFTESTWARNINGMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class SelfTestWarningMessageDialog;
}

class SelfTestWarningMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelfTestWarningMessageDialog(QWidget *parent = 0);
    ~SelfTestWarningMessageDialog();

private:
    Ui::SelfTestWarningMessageDialog *ui;
};

#endif // SELFTESTWARNINGMESSAGEDIALOG_H
