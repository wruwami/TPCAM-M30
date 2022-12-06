#ifndef SELFTESTDIALOG_H
#define SELFTESTDIALOG_H

#include <QDialog>

namespace Ui {
class SelfTestDialog;
}

class SelfTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelfTestDialog(QWidget *parent = 0);
    ~SelfTestDialog();

private:
    Ui::SelfTestDialog *ui;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SELFTESTDIALOG_H
