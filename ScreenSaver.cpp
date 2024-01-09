#include "ScreenSaver.h"
#include <QApplication>
#include <QDesktopWidget>

#include "Logger.h"

screensaver::screensaver(QWidget *parent)
    : QWidget(parent)
{
    backtimer=new QTimer(this);
    connect(backtimer,SIGNAL(timeout()),this,SLOT(screensaverstart()));
    powerofftimer = new QTimer(this);
    connect(powerofftimer,SIGNAL(timeout()),this,SLOT(PowerOff()));
}
screensaver::~screensaver()
{
    delete backtimer;
    delete powerofftimer;
}
void screensaver::timestart()
{
    backtimer->start(time);
}
bool screensaver::timeisactive()
{
    return backtimer->isActive();
}
void screensaver::timestop()
{
    backtimer->stop();
}

void screensaver::Setstart(bool start)
{
    m_bStart = start;
}

bool screensaver::Getstart()
{
    return m_bStart;
}

void screensaver::PowerOffTimerStart()
{
    powerofftimer->start(10*60*1000);
}

void screensaver::PowerOffTimerStop()
{
    powerofftimer->stop();
}

void screensaver::PowerOff()
{
    QEventLoop loop;
    SoundPlayer::GetInstance()->play(ReBooting);
    connect(SoundPlayer::GetInstance(), SIGNAL(audioStop()), &loop, SLOT(quit()));
    loop.exec();

    SetLogMsg(POWER_OFF);
    system("sudo systemctl poweroff -i");
}
void screensaver::settime(qint64 minute)
{
    time=minute*60*1000;
}
void screensaver::screensaverstart()//change picture
{
    timestop();
    SetPowerSavingMode(true);
    PowerOffTimerStart();
}
void screensaver::screensaverstop()//change picture
{
    timestart();
    SetPowerSavingMode(false);
    PowerOffTimerStop();
}

void screensaver::SetPowerSavingMode(bool bSet)
{
    if (bSet)
    {
        system("echo 0 > /sys/devices/platform/hud/display");
        system("echo 1 > /sys/class/backlight/backlight/bl_power");
    }
    else
    {
        system("echo 0 > /sys/class/backlight/backlight/bl_power");
        system("echo 1 > /sys/devices/platform/hud/display");
    }
}
