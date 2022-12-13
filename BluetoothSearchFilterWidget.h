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

private slots:
    void on_applyPushButton_clicked();

    void on_yesPushButton_clicked();

    void on_noPushButton_clicked();

private:
    Ui::BluetoothSearchFilterWidget *ui;
    QDialog* m_pParent;
};

#endif // BLUETOOTHSEARCHFILTERWIDGET_H
