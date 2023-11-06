#ifndef FTPTRANSTHREAD_H
#define FTPTRANSTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QSharedPointer>

#include <ftplib.h>

#include "ConfigManager.h"

class FtpTransThread : public QThread
{
    Q_OBJECT
public:
    explicit FtpTransThread(QObject *parent = nullptr);
    virtual ~FtpTransThread();
    void PushFile(QString);
private:
    void DoFtpTrans(QString);
private:
     QQueue<QString> m_FileQueue;
     QSharedPointer<QMutex> m_mutex;
     ConfigManager m_config = ConfigManager("parameter_setting6.json");
     ftplib m_ftp;/* = new ftplib();*/
signals:
     void sig_exit();
protected:
    void run() override;
};

#endif // FTPTRANSTHREAD_H
