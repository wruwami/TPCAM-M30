#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QtGui>
#include <QLabel>
#include <QWidget>
class screensaver:public QWidget
{
    Q_OBJECT
public:
    screensaver(QWidget *parent = 0);
    virtual ~screensaver();
    bool timeisactive();
    void screensaverstop();
    void settime(qint64 minute=1);
    void timestart();
    void timestop();
    void Setstart(bool);
    bool Getstart();
    void PowerOffTimerStart();
    void PowerOffTimerStop();
private:
    void SetPowerSavingMode(bool bSet);
private:
    QTimer *backtimer;
    QTimer *powerofftimer;

    qint64  time;
    bool m_bStart = false;
    bool m_bPowerSavingMode = false;
public slots:
    void PowerOff();
    void screensaverstart();
};

#endif // SCREENSAVER_H
