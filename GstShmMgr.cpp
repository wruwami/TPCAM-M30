#include "GstShmMgr.h"
#include <thread>
#include <chrono>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>


void thread_CommandExcute(QString strCommand, QString strFileFullName, QString strFileFullName2)
{
    int fileDescriptor = ::open(strFileFullName.toStdString().c_str(), O_CREAT | O_WRONLY, 0666);

    int result = std::system(strCommand.toStdString().c_str());

    flock(fileDescriptor, LOCK_UN);
    // Close the file descriptor
    if (::close(fileDescriptor) == -1) {
//            return;
    }

    QFile lockFile(strFileFullName2 + ".lock");
    lockFile.remove();

    qDebug() << strCommand << " : " << result;
}

GstShmMgr* GstShmMgr::m_pInstance = nullptr;

GstShmMgr::GstShmMgr()
    : m_pGstShmPross(nullptr)
{
    qDebug() << "GstShmMgr constructor called!";
    setShmsink(SHM_NAME, SHM_DEV);
    //GstShmMgr::getInstance();
}
GstShmMgr::~GstShmMgr()
{
    qDebug() << "GstShmMgr destructor called!";
    m_pGstShmPross->close();
    delete m_pGstShmPross;
    m_pGstShmPross = nullptr;
}

void GstShmMgr::setShmsink(QString qstrShmName, QString qstrDevice)
{
    m_pGstShmPross = new QProcess;
    QString strShmsinkCommand = "gst-launch-1.0 rkisp device=" + qstrDevice + " io-mode=1 ! video/x-raw,format=NV12,width=1920,height=1080,framerate=30/1 ! videoconvert ! shmsink socket-path=/tmp/foo name=" + qstrShmName + " sync=false wait-for-connection=false shm-size=20000000";
    m_pGstShmPross->startDetached(strShmsinkCommand);
    //m_pGstShmPross->start(strShmsinkCommand);
}

void GstShmMgr::saveVideoUseShmsrc(QString qstrVideoFilename, QString qstrPath, QString qstrShmName, int nRecodeTime, int nFramerate, int nVideoWidth, int nVideoHeight)
{
    qDebug() << "video path : " << qstrPath + qstrShmName;

    if (qstrPath != "")
    {
        mkDirs(qstrPath);
    }

    int nNumBuffer = nRecodeTime * nFramerate;
    /*QString qstrTimestamp = (bTimestamp) ? "! clockoverlay valignment=bottom halignment=left font-desc=\"Sans, 12\" time-format=\"%F %X\"" : "";
    QString qstrTextoverlay = "";
    if (bTextoverlay)
    {
        qstrTextoverlay.sprintf("! textoverlay text=\"%s\" valignment=bottom halignment=right font-desc=\"Sans, 12\"", qstrEnfoceInfo.toStdString().c_str());
    }
    QString strCommand = QString("gst-launch-1.0 shmsrc num-buffers=%1 do-timestamp=true socket-path=/tmp/foo name=%2 ! video/x-raw,format=NV12,width=%3,height=%4,framerate=%5/1 %6 %7 ! videoconvert ! jpegenc ! queue ! mux. alsasrc num-buffers=1024 ! audioconvert ! \'audio/x-raw,rate=44100,channels=2\' ! queue ! mux. avimux name=mux ! filesink location=%8%9"
        ).arg(QString::number(nNumBuffer), qstrShmName, QString::number(nVideoWidth), QString::number(nVideoHeight), QString::number(nFramerate), qstrTimestamp, qstrTextoverlay, qstrPath, qstrVideoFilename);
    */


    QString strCommand = QString("gst-launch-1.0 shmsrc num-buffers=%1 do-timestamp=true socket-path=/tmp/foo name=%2 ! video/x-raw,format=NV12,width=1920,height=1080,framerate=%3/1 ! queue ! videoscale ! video/x-raw,format=NV12,width=%4,height=%5 ! videoconvert ! jpegenc ! avimux ! filesink location=%6%7"
        ).arg(QString::number(nNumBuffer), qstrShmName, QString::number(nFramerate), QString::number(nVideoWidth), QString::number(nVideoHeight), qstrPath, qstrVideoFilename);

    int fileDescriptor = ::open((qstrPath+qstrShmName).toStdString().c_str(), O_CREAT | O_WRONLY, 0666);
    if (flock(fileDescriptor, LOCK_EX) != 0) {
//            return;
    }

    QFile lockFile(qstrPath+qstrVideoFilename + ".lock");
    lockFile.open(QIODevice::WriteOnly);
    lockFile.write("");
    lockFile.close();

    std::thread thread_command(thread_CommandExcute, strCommand, qstrPath+qstrShmName, qstrPath+qstrVideoFilename);
    thread_command.detach();

    // Close the file descriptor
    if (::close(fileDescriptor) == -1) {
//        return;
    }
}

void GstShmMgr::mkDirs(QString dir_path)
{
    QDir dir(dir_path);

    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    QFile::Permissions permissions = QFile::ReadUser | QFile::WriteUser | QFile::ExeUser |
        QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup |
        QFile::ReadOther | QFile::WriteOther | QFile::ExeOther;
    QFile::setPermissions(dir_path, permissions);
}
