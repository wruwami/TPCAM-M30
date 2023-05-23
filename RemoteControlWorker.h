#ifndef REMOTECONTROLWORKER_H
#define REMOTECONTROLWORKER_H

#include <QObject>
#include "MainWindow.h"

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
    void start(const QString &);
    void resultReady(const QString &result);
};

#endif // REMOTECONTROLWORKER_H
