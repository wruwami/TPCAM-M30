#ifndef REMOTECONTROLWORKER_H
#define REMOTECONTROLWORKER_H

#include <QObject>
#include "MainWindow.h"

class MainWindow;
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
