#ifndef REMOTECONTROLWORKER_H
#define REMOTECONTROLWORKER_H

#include <QObject>

class RemoteControlWorker : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControlWorker(QObject *parent = nullptr);
    virtual ~RemoteControlWorker();

public slots:
    void doWork();

signals:
    void start(const QString &);
    void resultReady(const QString &result);
};

#endif // REMOTECONTROLWORKER_H
