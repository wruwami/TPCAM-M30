#ifndef SETTING6BLUETOOTHSEARCHFILTERDIALOG_H
#define SETTING6BLUETOOTHSEARCHFILTERDIALOG_H

#include <QDialog>

namespace Ui {
class Setting6BluetoothSearchFilterDialog;
}

class Setting6BluetoothSearchFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting6BluetoothSearchFilterDialog(QWidget *parent = 0);
    ~Setting6BluetoothSearchFilterDialog();

private:
    Ui::Setting6BluetoothSearchFilterDialog *ui;
};

#endif // SETTING6BLUETOOTHSEARCHFILTERDIALOG_H
