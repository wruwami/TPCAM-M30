#include "FtpTransThread.h"

#include <QFile>

#include "ConfigManager.h"
#include "FileManager.h"


FtpTransThread::FtpTransThread(QObject *parent)
    : QThread{parent}
{
    QJsonObject jsonObject = m_config.GetConfig();
    m_ftp.Connect(QString(jsonObject["ftp server( dns )"].toString() + ":" + std::to_string(jsonObject["ftp port"].toInt()).c_str()).toStdString().c_str());
    m_ftp.Login(jsonObject["ftp user name"].toString().toStdString().c_str(), jsonObject["ftp password"].toString().toStdString().c_str());

    m_mutex.reset(new QMutex);
}

FtpTransThread::~FtpTransThread()
{
    m_ftp.Quit();
}

void FtpTransThread::PushFile(QString file_name)
{
    m_mutex->lock();
    m_FileQueue.enqueue(file_name);
    m_mutex->unlock();
}

void FtpTransThread::DoFtpTrans(QString file_name)
{
    char targetDir[1024];
    m_ftp.Pwd(targetDir, 1024);

    QString dir = file_name.replace(GetSDPath(), QString(targetDir));
    dir.replace("\"", "");
    m_ftp.Mkdir(dir.toStdString().c_str());

    QString fileName = file_name.replace(GetSDPath(), QString(targetDir));
    fileName.replace("\"", "");

    m_ftp.Put(file_name.toStdString().c_str(), fileName.toStdString().c_str(), ftplib::image);

}

void FtpTransThread::run()
{
    forever{
        if ( QThread::currentThread()->isInterruptionRequested() )
            return;

        m_mutex->lock();
        QString file_name;
        if (m_FileQueue.size() > 0)
            file_name = m_FileQueue.dequeue();
//        m_FileQueue.pop_front();
        m_mutex->unlock();

        QFile file(file_name);
        if (file.exists())
            DoFtpTrans(file_name);
        else
        {
            m_mutex->lock();
            m_FileQueue.enqueue(file_name);
            m_mutex->unlock();
        }
        msleep(1);

    }
}
