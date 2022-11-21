#ifndef SETTING3PASSWORDCHANGINGDIALOG_H
#define SETTING3PASSWORDCHANGINGDIALOG_H

#include <QDialog>

namespace Ui {
class Setting3PasswordChangingDialog;
}

class Setting3PasswordChangingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting3PasswordChangingDialog(QWidget *parent = 0);
    ~Setting3PasswordChangingDialog();

private:
    Ui::Setting3PasswordChangingDialog *ui;
};

#endif // SETTING3PASSWORDCHANGINGDIALOG_H
