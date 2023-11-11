#ifndef FTPTRANSTHREAD2_H
#define FTPTRANSTHREAD2_H

#include <QThread>
#include <QSharedPointer>
#include <QMutex>

class FtpTransThread2 : public QThread
{
    Q_OBJECT
public:
    explicit FtpTransThread2(QObject *parent = nullptr);
    virtual ~FtpTransThread2();
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

#endif // FTPTRANSTHREAD2_H
