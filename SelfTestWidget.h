/**
 * @file SelfTestWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 셀프테스트 표시 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SELFTESTWIDGET_H
#define SELFTESTWIDGET_H

#include <QWidget>
#include "ltc2943.h"
#include "SerialViscaManager.h"
#include "SerialLaserManager.h"

enum Status{
    Fail = 0,
    Pass = 1,
    Check = 2,
};

namespace Ui {
class SelfTestWidget;
}

class SelfTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelfTestWidget(QWidget *parent = 0);
    ~SelfTestWidget();

private:
    QString GetVersion();
    void StartSelfTest();
    void CameraTest();
    void LaserTest();
    bool BatteryTest();
    bool StorageTest();
public:
    Status GetCamera();
    Status GetLaser();
    Status GetStorage();
    Status GetBattery();
    Status m_nCamera = Check;
    Status m_nLaser = Check;
    Status m_nBattery = Check;
    Status m_nStorage = Check;
    unsigned char send_data;
private:
    Ui::SelfTestWidget *ui;
    int m_nSecond = 0;
    LTC2943 ltc = LTC2943(15);
    SerialViscaManager m_serialViscaManager;
    SerialLaserManager m_serialLaserManager;
    QTimer* m_Timer;
    int m_id = 0;
    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
signals:
    void selftest_finished();
};

#endif // SELFTESTWIDGET_H
