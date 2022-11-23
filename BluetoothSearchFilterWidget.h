#ifndef BLUETOOTHSEARCHFILTERWIDGET_H
#define BLUETOOTHSEARCHFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class BluetoothSearchFilterWidget;
}

class BluetoothSearchFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothSearchFilterWidget(QWidget *parent = 0);
    ~BluetoothSearchFilterWidget();

private:
    Ui::BluetoothSearchFilterWidget *ui;
};

#endif // BLUETOOTHSEARCHFILTERWIDGET_H
