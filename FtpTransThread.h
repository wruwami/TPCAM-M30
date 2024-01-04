/**
 * @file FtpTransThread.h
 * @author wruwami (wruwami@naver.com)
 * @brief 단속화면 FTP 전송을 수행하는 Thread
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FTPTRANSTHREAD_H
#define FTPTRANSTHREAD_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QSharedPointer>

#include <ftplib.h>

#include "ConfigManager.h"

/**
 * @brief 단속화면 FTP 전송을 수행하는 Thread 클래스
 * 
 */
class FtpTransThread : public QThread
{
    Q_OBJECT
public:
    explicit FtpTransThread(QObject *parent = nullptr);
    virtual ~FtpTransThread();
    void PushFile(QString);
private:
    int DoFtpTrans(QString);
private:
     QSharedPointer<QQueue<QString>> m_FileQueue;
     QSharedPointer<QMutex> m_mutex;
     ConfigManager m_config = ConfigManager("parameter_setting6.json");
     ftplib m_ftp;/* = new ftplib();*/
signals:
     void push_file(QString);
//     void sig_exit();
protected slots:
     void on_push_file(QString);
protected:
    void run() override;
};

#endif // FTPTRANSTHREAD_H
