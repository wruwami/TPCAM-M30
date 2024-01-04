/**
 * @file ScreenSaver.h
 * @author wruwami (wruwami@naver.com)
 * @brief Power Saving 기능이 구현되어 있는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QtGui>
#include <QLabel>
#include <QWidget>

#include "SoundPlayer.h"

/**
 * @brief Power Saving 기능이 구현되어 있는 클래스
 * 
 */
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
    SoundPlayer *powerOffSound;

public slots:
    void PowerOff();
    void screensaverstart();
};

#endif // SCREENSAVER_H
