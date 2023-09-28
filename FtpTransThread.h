#ifndef FTPTRANSTHREAD_H
#define FTPTRANSTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QSharedPointer>

#include <ftplib.h>

#include "ConfigManager.h"

enum FTPMode {
    FileManagerMode,
    EnforcementMode
};

class FtpTransThread : public QThread
{
public:
    explicit FtpTransThread(FTPMode, QObject *parent = nullptr);
    virtual ~FtpTransThread();
    void PushFile(QString);
private:
    void DoFtpTrans(QString);
private:
     QQueue<QString> m_FileQueue;
     QSharedPointer<QMutex> m_mutex;
     ConfigManager m_config = ConfigManager("parameter_setting6.json");
     ftplib m_ftp;/* = new ftplib();*/
     FTPMode m_Mode;

protected:
    void run() override;
};

#endif // FTPTRANSTHREAD_H
