#ifndef SETTING4ADMINPWDIALOG_H
#define SETTING4ADMINPWDIALOG_H

#include <QDialog>

namespace Ui {
class Setting4AdminPWDialog;
}

class Setting4AdminPWDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting4AdminPWDialog(QWidget *parent = 0);
    ~Setting4AdminPWDialog();

private:
    Ui::Setting4AdminPWDialog *ui;
};

#endif // SETTING4ADMINPWDIALOG_H
