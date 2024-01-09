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

/**
 * @brief QApplication 상속받아 파워 세이버 기능 추가한 클래스
 * 
 */
class Application : public QApplication
{
public:
    Application(int & argc, char ** argv);
    virtual ~Application();
    bool notify(QObject *, QEvent *);
    screensaver* send();
private:
    screensaver *_screensaver = nullptr;
};

#endif // APPLICATION_H
