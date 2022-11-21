#ifndef SETTING1LOCATIONDIALOG_H
#define SETTING1LOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class Setting1LocationDialog;
}

class Setting1LocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting1LocationDialog(QWidget *parent = 0);
    ~Setting1LocationDialog();

private:
    Ui::Setting1LocationDialog *ui;
};

#endif // SETTING1LOCATIONDIALOG_H
