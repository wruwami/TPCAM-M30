#ifndef ADMINPWDIALOG_H
#define ADMINPWDIALOG_H

#include <QDialog>

namespace Ui {
class AdminPWDialog;
}

class AdminPWDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPWDialog(QWidget *parent = 0);
    ~AdminPWDialog();

private:
    Ui::AdminPWDialog *ui;
};

#endif // ADMINPWDIALOG_H
