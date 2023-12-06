/**
 * @file DeviceIDWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief admin-align유저가 device ID를 수정할 수 있는 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DEVICEIDWIDGET_H
#define DEVICEIDWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class DeviceIDWidget;
}

class DeviceIDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceIDWidget(QWidget *parent = 0);
    ~DeviceIDWidget();
public:
    CustomPushButton* m_pSaveButton;
    CustomPushButton* m_pCancelButton;
private slots:
    void on_inputPushButton_clicked();

    void on_savePushButton_clicked();

private:
    Ui::DeviceIDWidget *ui;
};

#endif // DEVICEIDWIDGET_H
