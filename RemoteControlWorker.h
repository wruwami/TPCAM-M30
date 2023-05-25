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
    void doFirstAction();

signals:
    void start(MainWindow*);
    void resultReady(const QString &result);
    void FirstAction();
};

#endif // REMOTECONTROLWORKER_H
