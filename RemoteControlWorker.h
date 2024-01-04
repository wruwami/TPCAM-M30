/**
 * @file RemoteControlWorker.h
 * @author wruwami (wruwami@naver.com)
 * @brief RemoteController 기능이 구현되어 있는 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef REMOTECONTROLWORKER_H
#define REMOTECONTROLWORKER_H

#include <QObject>
#include "MainWindow.h"

class MainWindow;
/**
 * @brief RemoteController 기능이 구현되어 있는 클래스
 * 
 */
class RemoteControlWorker : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControlWorker(MainWindow* mainwindow, QObject *parent = nullptr);
    virtual ~RemoteControlWorker();
private:
    MainWindow* m_pMainwindow;
public slots:
    void doWork();

signals:
    void start(MainWindow*);
    void resultReady(const QString &result);
    void FirstAction();
    void SecondAction();
    void ThirdAction();
    void ForthAction();
    void FifththAction();
    void SharpAction();
    void StarAction();
    void ZeroAction();
    void NinethAction();

};

#endif // REMOTECONTROLWORKER_H
