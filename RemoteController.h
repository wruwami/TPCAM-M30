/**
 * @file RemoteController.h
 * @author wruwami (wruwami@naver.com)
 * @brief RemoteControllerWorker를 구동시키는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

//#include <QQueue>
#include <QObject>
#include <QSharedPointer>

class QThread;
class MainWindow;
/**
 * @brief RemoteControllerWorker를 구동시키는 클래스
 * 
 */
class RemoteController
{
public:
    RemoteController(MainWindow *parent = nullptr);
    int Start();
    void CreateThread();
private:
    MainWindow* m_pMainwindow;
    QSharedPointer<QThread> m_thread;
//    QQueue<int> m_queue;
};

#endif // REMOTECONTROLLER_H
