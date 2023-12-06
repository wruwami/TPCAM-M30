/**
 * @file FileTransThread.h
 * @author wruwami (wruwami@naver.com)
 * @brief USB파일 전송시 사용되는 Thread
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILETRANSTHREAD_H
#define FILETRANSTHREAD_H

#include <QThread>
#include <QMutex>
#include <QSharedPointer>

class FileTransThread : public QThread
{
    Q_OBJECT
public:
    explicit FileTransThread(QObject *parent = nullptr);
    virtual ~FileTransThread();
private:
    QSharedPointer<QMutex> m_mutex;
    int m_count = 0;
signals:
    void setMaximum(int);
    void setValue(int);
    void setFileNameText(QString);
    void setFileCountText(QString);
//    void sig_exit();
//    void close2();
protected:
    void run() override;

};

#endif // FILETRANSTHREAD_H
