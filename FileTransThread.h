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
private:
    QSharedPointer<QMutex> m_mutex;
    int m_count = 0;
signals:
    void setMaximum(int);
    void setValue(int);
    void setFileNameText(QString);
    void setFileCountText(QString);
protected:
    void run() override;

};

#endif // FILETRANSTHREAD_H
