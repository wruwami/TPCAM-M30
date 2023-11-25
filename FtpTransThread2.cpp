#include "FtpTransThread2.h"

#include "qdir.h"
#include <QDirIterator>
#include <QDebug>

#include "ftplib.h"
#include "ConfigManager.h"
#include "FileManager.h"

FtpTransThread2::FtpTransThread2(QObject *parent)
    : QThread{parent}
{

}

FtpTransThread2::~FtpTransThread2()
{
    m_ftp->Quit();
    if (isRunning())
    {
        requestInterruption();

    }
    delete m_ftp;
    m_ftp = nullptr;

    quit();
    wait();
}

void FtpTransThread2::run()
{
    //    ui->oneProgressBar->setValue(0);
        emit setValue(0);
    //    buttonsEnabled(true);

    //    QNetworkAccessManager *accessManager=new QNetworkAccessManager(this);
    //    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

        ConfigManager config = ConfigManager("parameter_setting6.json");
        QJsonObject jsonObject = config.GetConfig();

        m_ftp = new ftplib();
    //    qDebug() << QString(jsonObject["ftp server( dns )"].toString() + ":" + ;
        int ret = m_ftp->Connect(QString(jsonObject["ftp server( dns )"].toString() + ":" + std::to_string(jsonObject["ftp port"].toInt()).c_str()).toStdString().c_str());
        if (ret == 0)
        {
            return;
        }

        ret = m_ftp->Login(jsonObject["ftp user name"].toString().toStdString().c_str(), jsonObject["ftp password"].toString().toStdString().c_str());
        if (ret == 0)
        {
            return;
        }

        char targetDir[1024];
        m_ftp->Pwd(targetDir, 1024);
        if (!strcmp(targetDir, ""))
        {
            return;
        }

        QDir qdir(GetSDPath());
        QDirIterator iterDir(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while (iterDir.hasNext())
        {
            iterDir.next();
            m_count++;
        }

        QDirIterator iterDir3(GetSDPath(), QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while (iterDir3.hasNext())
        {
            QString dir = iterDir3.next().replace(GetSDPath() + "/", "");
            dir.replace("\"", "");
            if (!m_ftp->Mkdir(dir.toStdString().c_str()))
            {
                qDebug() << "ftp mkdir failed";
            }
         }


        QDirIterator iterDir2(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

        emit setMaximum(m_count);
        emit setValue(0);
        int i = 0;
        while (iterDir2.hasNext())
        {

    //        i++;
            QString fileName = iterDir2.next();
            QString targetFileName = fileName;
            targetFileName = targetFileName.replace(GetSDPath() + "/", "");
            targetFileName.replace("\"", "");
            QString filePath;
            if (m_ftp == nullptr)
                return;
            if (!m_ftp->Put(fileName.toStdString().c_str(), targetFileName.toStdString().c_str(), ftplib::image))
            {
                qDebug() << "ftp put failed";
            }
            emit setValue(++i);
            emit setFileCountText(QString("%1 / %2").arg(i).arg(m_count));
            emit setFileNameText(fileName);

            if ( QThread::currentThread()->isInterruptionRequested() )
            {
                if (m_ftp)
                    m_ftp->Quit();
                return;
            }

    //        ftp.put_file(fileName.toStdString().c_str());

    //        QString iterDir2.next();

    //        QUrl url;
    //        url.setScheme("ftp");
    //        url.setHost(jsonObject["ftp server( dns )"].toString());

    //        url.setPort(jsonObject["ftp port"].toInt());
    //        url.setUserName(jsonObject["ftp user name"].toString());
    //        url.setPassword(jsonObject["ftp password"].toString());
    //        url.setPath(QString(ret.c_str()) + iterDir2.filePath());
    ////        url.setPath(QString("d:") + iterDir2.filePath().replace("/", "\\"));
    ////        qDebug() << QString("d:") + iterDir2.filePath().replace("/", "\\");
    ////        QString file_path(iterDir2.fileName());
    ////        int index = file_path.lastIndexOf('/');
    ////        QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
    ////        url.setPath(QString(ret.c_str()) + "/" + file_name);

    //        ui->fileNameLabel->setText(iterDir2.fileName());

    //        QByteArray byte_file;
    //        QNetworkRequest request(url);
    //        QNetworkReply* reply;

    //        QFile file(QString(iterDir2.filePath()));
    //        file.open(QIODevice::ReadOnly);
    //        byte_file=file.readAll();
    //        reply = accessManager->put(request, byte_file);

    //        connect(reply, SIGNAL(uploadProgress(qint64 ,qint64)), SLOT(loadProgress(qint64 ,qint64)));
        }
        m_ftp->Quit();
//        emit sig_exit();
}

//void FtpTransThread2::close2()
//{
//    this->requestInterruption();
//}
