#include "FtpTransThread.h"

#include <QFile>
#include <QFileInfo>

#include "ConfigManager.h"
#include "FileManager.h"


FtpTransThread::FtpTransThread(QObject *parent)
    : QThread{parent}
{


//    if (jsonObject["ftp select"].toInt() != 3)
//        this->exit();

    m_mutex.reset(new QMutex);
}

FtpTransThread::~FtpTransThread()
{
    if (isRunning())
    {
        requestInterruption();
    }
    quit();
    wait();
}

void FtpTransThread::PushFile(QString file_name)
{
    m_mutex->lock();
    m_FileQueue.enqueue(file_name);
    m_mutex->unlock();
}

int FtpTransThread::DoFtpTrans(QString file_name)
{
    char targetDir[1024];
    int ret = 1;

    if (!m_ftp.Pwd(targetDir, 1024))
    {
        return 0;
    }

    QString target_file_name = file_name;
    QString dir = target_file_name.replace(GetSDPath() + "/", QString(targetDir));
    QFileInfo fi(dir);
    dir = fi.absolutePath();
    dir.replace("\"", "");
    std::string dir2 = dir.toStdString();
    dir2 = dir2.substr(0, dir2.rfind("/"));
    if (!m_ftp.Mkdir(dir2.c_str()))
    {
        return 0;
    }

    if (!m_ftp.Mkdir(dir.toStdString().c_str()))
    {
        return 0;
    }


//    QString fileName = file_name.replace(GetSDPath(), QString(targetDir));
    target_file_name.replace("\"", "");

    if (!m_ftp.Put(file_name.toStdString().c_str(), target_file_name.toStdString().c_str(), ftplib::image))
    {
        return 0;
    }
    return ret;
}

void FtpTransThread::run()
{
    QJsonObject jsonObject = m_config.GetConfig();

    int ret = m_ftp.Connect(QString(jsonObject["ftp server( dns )"].toString() + ":" + std::to_string(jsonObject["ftp port"].toInt()).c_str()).toStdString().c_str());
    if (ret == 0)
        return;
    ret = m_ftp.Login(jsonObject["ftp user name"].toString().toStdString().c_str(), jsonObject["ftp password"].toString().toStdString().c_str());
    if (ret == 0)
        return;

    forever{

        m_mutex->lock();
        QString file_name;
        if (m_FileQueue.size() > 0)
            file_name = m_FileQueue.dequeue();
//        m_FileQueue.pop_front();
        m_mutex->unlock();

        QFile file(file_name);
        if (file.exists())
            DoFtpTrans(file_name);
        else if (!file_name.isEmpty())
        {
            m_mutex->lock();
            m_FileQueue.enqueue(file_name);
            m_mutex->unlock();
        }
        msleep(1);

        if ( QThread::currentThread()->isInterruptionRequested() )
        {
            m_ftp.Quit();
            return;
        }
    }

    return;
}
