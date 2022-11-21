#ifndef SETTING4WIFISEARCHDIALOG_H
#define SETTING4WIFISEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class Setting4WifiSearchDialog;
}

class Setting4WifiSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting4WifiSearchDialog(QWidget *parent = 0);
    ~Setting4WifiSearchDialog();

private:
    Ui::Setting4WifiSearchDialog *ui;
};

#endif // SETTING4WIFISEARCHDIALOG_H
