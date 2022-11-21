#ifndef SETTING3SYSTEMINFOMATIONDIALOG_H
#define SETTING3SYSTEMINFOMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class Setting3SystemInfomationDialog;
}

class Setting3SystemInfomationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting3SystemInfomationDialog(QWidget *parent = 0);
    ~Setting3SystemInfomationDialog();

private:
    Ui::Setting3SystemInfomationDialog *ui;
};

#endif // SETTING3SYSTEMINFOMATIONDIALOG_H
