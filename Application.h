/**
 * @file Application.h
 * @author wruwami (wruwami@naver.com)
 * @brief Power Saving 기능 구현 class
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef APPLICATION_H
#define APPLICATION_H


#include <QApplication>
#include <QDebug>
#include "ScreenSaver.h"
#include "SoundPlayer.h"

class Application : public QApplication
{
public:
    Application(int & argc, char ** argv);
    bool notify(QObject *, QEvent *);
    screensaver* send();
private:
    screensaver *_screensaver;
    SoundPlayer soundPlayer = SoundPlayer("button.mp3");
};

#endif // APPLICATION_H
