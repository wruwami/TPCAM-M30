#ifndef SETTING3ADMINPWDIALOG_H
#define SETTING3ADMINPWDIALOG_H

#include <QDialog>

namespace Ui {
class Setting3AdminPWDialog;
}

class Setting3AdminPWDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting3AdminPWDialog(QWidget *parent = 0);
    ~Setting3AdminPWDialog();

private:
    Ui::Setting3AdminPWDialog *ui;
};

#endif // SETTING3ADMINPWDIALOG_H
