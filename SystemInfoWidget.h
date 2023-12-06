/**
 * @file SystemInfoWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 시스템 정보 화면 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include <QWidget>

class SerialViscaManager;
namespace Ui {
class SystemInfoWidget;
}

class SystemInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemInfoWidget(QWidget *parent = 0);
    ~SystemInfoWidget();
private:
    void MoveFactorySetting();
private:
    Ui::SystemInfoWidget *ui;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void sig_cam_version();
    void sig_laser_version();

protected slots:
    void on_cam_version(int, int);
    void on_laser_version(QString);
};

#endif // SYSTEMINFOWIDGET_H
