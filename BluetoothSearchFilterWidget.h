/**
 * @file BluetoothSearchFilterWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 블루투스 검색 위젯(현재 사용되지 않음)
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BLUETOOTHSEARCHFILTERWIDGET_H
#define BLUETOOTHSEARCHFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class BluetoothSearchFilterWidget;
}

/**
 * @brief 블루투스 검색 위젯 클래스
 * 
 */
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
