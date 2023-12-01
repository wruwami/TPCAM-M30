#include "FtpTransThread.h"

#include <fstream>

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QLockFile>

#include "ConfigManager.h"
#include "FileManager.h"


FtpTransThread::FtpTransThread(QObject *parent)
    : QThread{parent}
{


//    if (jsonObject["ftp select"].toInt() != 3)
//        this->exit();

    m_FileQueue.reset(new QQueue<QString>);
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
    m_FileQueue->enqueue(file_name);
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
    QString dir = target_file_name.replace(GetSDPath() + "/", "");

    int index = dir.lastIndexOf("/");
    dir = dir.mid(0, index);
    std::string dir2 = dir.toStdString();
    dir2 = dir2.substr(0, dir2.rfind("/"));
    qDebug() << dir2.c_str();
    if (!m_ftp.Mkdir(dir2.c_str()))
    {
        qDebug() << "mkdir failed";
    }

    if (!m_ftp.Mkdir(dir.toStdString().c_str()))
    {
        qDebug() << "mkdir failed";
    }


//    QString fileName = file_name.replace(GetSDPath(), QString(targetDir));
    target_file_name.replace("\"", "");

    if (!m_ftp.Put(file_name.toStdString().c_str(), target_file_name.toStdString().c_str(), ftplib::image))
    {
        qDebug() << "put failed";
    }
    return ret;
}

void FtpTransThread::on_push_file(QString file_name)
{
    m_mutex->lock();
    m_FileQueue->enqueue(file_name);
    m_mutex->unlock();
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
        if (m_FileQueue->size() > 0)
            file_name = m_FileQueue->dequeue();
        else
        {
            m_mutex->unlock();
            continue;
        }
//        m_FileQueue.pop_front();
        m_mutex->unlock();

        QFile file(file_name);
        if (file.exists())
        {
            QFile lockFile(file_name + ".lock");
            if (!lockFile.exists())
            {
                DoFtpTrans(file_name);
            }
            else
            {
                m_mutex->lock();
                m_FileQueue->enqueue(file_name);
                m_mutex->unlock();
            }
        }
        else if (!file_name.isEmpty())
        {
            m_mutex->lock();
            m_FileQueue->enqueue(file_name);
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
