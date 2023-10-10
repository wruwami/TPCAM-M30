#include "FileTransThread.h"

#include "qdir.h"
#include <QDirIterator>
#include <QDebug>

#include "FileManager.h"


FileTransThread::FileTransThread(QObject *parent)
    : QThread{parent}
{
    if (GetUSBPath() == "")
        this->requestInterruption();
}

void FileTransThread::run()
{
    emit setValue(0);
//        ui->allProgressBar->setValue(0);
        QString dir = GetUSBPath();
        QDir qdir(GetSDPath());
        QDirIterator iterDir(GetSDPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while (iterDir.hasNext())
        {
            iterDir.next();

            qDebug() << iterDir.fileName();

            m_count++;

    //        ui->listWidget->addItem(iterDir.fileName());
        }

        QDirIterator iterDir3(GetSDPath(), QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDirIterator::Subdirectories);
        while (iterDir3.hasNext())
        {
            QString dir2 = iterDir3.next().replace(GetSDPath(), QString(dir));
            dir2.replace("\"", "");
    //        QDir qdir2(dir2);
            qdir.mkdir(dir2);
    //        ftp.Mkdir(dir.toStdString().c_str());
         }

//        ui->allProgressBar->setMaximum(m_count);
        emit setMaximum(m_count);
        int i = 0;
        QDirIterator iterDir2(GetSDPath(), QDir::Files | QDir::NoDotAndDotDot |QDir::NoSymLinks, QDirIterator::Subdirectories);
        emit setValue(0);
        while (iterDir2.hasNext())
        {
            if ( QThread::currentThread()->isInterruptionRequested() )
                return;

            i++;

            QString fileName = iterDir2.next();
            QString targetFileName = fileName;
            targetFileName = targetFileName.replace(GetSDPath(), GetUSBPath());
            targetFileName.replace("\"", "");
            QString file_path(iterDir2.fileName());
            int index = file_path.lastIndexOf('/');
            QString file_name = file_path.mid(index + 1, file_path.size() - index - 1);
            emit setFileNameText(QString(file_name));
//            ui->fileNameLabel->setFontSize(23);
//            ui->allProgressBar->setValue((++i) / m_count);
            emit setFileCountText(QString("%1 / %2").arg(i).arg(m_count));
//            ui->fileCountLabel->setFontSize(23);


            QFile file(fileName);
//            ui->allProgressBar->setValue(++i);
            emit setValue(i);
    //        qDebug() << iterDir2.next();
    //        qDebug() << fileName;

            file.copy(targetFileName);
        }
    emit sig_exit();
}

//void FileTransThread::close2()
//{
//    this->requestInterruption();
//}
