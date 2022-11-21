#ifndef LOGINEXPIREDDATEDIALOG_H
#define LOGINEXPIREDDATEDIALOG_H

#include <QDialog>

namespace Ui {
class LoginExpiredDateDialog;
}

class LoginExpiredDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginExpiredDateDialog(QWidget *parent = 0);
    ~LoginExpiredDateDialog();

private:
    Ui::LoginExpiredDateDialog *ui;
};

#endif // LOGINEXPIREDDATEDIALOG_H
