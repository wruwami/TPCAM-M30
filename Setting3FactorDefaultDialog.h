#ifndef SETTING3FACTORDEFAULTDIALOG_H
#define SETTING3FACTORDEFAULTDIALOG_H

#include <QDialog>

namespace Ui {
class Setting3FactorDefaultDialog;
}

class Setting3FactorDefaultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting3FactorDefaultDialog(QWidget *parent = 0);
    ~Setting3FactorDefaultDialog();

private:
    Ui::Setting3FactorDefaultDialog *ui;
};

#endif // SETTING3FACTORDEFAULTDIALOG_H
