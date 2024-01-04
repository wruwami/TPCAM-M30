/**
 * @file FtpTransThread2.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일매니저 FTP 전송시 사용되는 쓰레드
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FTPTRANSTHREAD2_H
#define FTPTRANSTHREAD2_H

#include <QThread>
#include <QSharedPointer>
#include <QMutex>

class ftplib;
/**
 * @brief 파일매니저 FTP 전송시 사용되는 쓰레드 클래스
 * 
 */
class FtpTransThread2 : public QThread
{
    Q_OBJECT
public:
    explicit FtpTransThread2(QObject *parent = nullptr);
    virtual ~FtpTransThread2();
private:
//    QSharedPointer<QMutex> m_mutex;
    int m_count = 0;
    ftplib* m_ftp;

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

#endif // FTPTRANSTHREAD2_H
