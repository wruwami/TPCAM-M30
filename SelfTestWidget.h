#ifndef SELFTESTWIDGET_H
#define SELFTESTWIDGET_H

#include <QWidget>
#include "ltc2943.h"

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
    bool m_isCamera = false;
    bool m_isLaser = false;
    bool m_isBattery = false;
    bool m_isStorage = false;

private:
    Ui::SelfTestWidget *ui;
    int m_nSecond = 0;
    LTC2943 ltc = LTC2943(15);

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SELFTESTWIDGET_H
