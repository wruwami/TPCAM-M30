#ifndef SELFTESTWIDGET_H
#define SELFTESTWIDGET_H

#include <QWidget>
#include "ltc2943.h"
#include "SerialViscaManager.h"
#include "SerialLaserManager.h"

enum Status{
    Check,
    Pass,
    Fail,
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
    bool CameraTest();
    bool LaserTest();
    bool BatteryTest();
    bool StorageTest();
public:
    Status m_nCamera = Check;
    Status m_nLaser = Check;
    Status m_nBattery = Check;
    Status m_nStorage = Check;

private:
    Ui::SelfTestWidget *ui;
    int m_nSecond = 0;
    LTC2943 ltc = LTC2943(15);
    SerialViscaManager m_serialViscaManager;
    SerialLaserManager m_serialLaserManager;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SELFTESTWIDGET_H
