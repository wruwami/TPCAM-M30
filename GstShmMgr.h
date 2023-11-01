#ifndef GSTSHMMGR_H
#define GSTSHMMGR_H

#include <QProcess>
#include <QString>
//#include <QSharedPointer>
#include "capture_thread.h"

#define SHM_NAME	QString("/tmp/shm")
#define SHM_DEV		QString("/dev/video1")

class GstShmMgr
{
private:
    static GstShmMgr* m_pInstance;
    QProcess* m_pGstShmPross;
    //std::shared_ptr<CaptureThread> m_pViewer;
    //QSharedPointer<CaptureThread> m_pViewer;
    CaptureThread* m_pViewer;
public:
    static GstShmMgr* getInstance()
    {
        if(m_pInstance == nullptr)
        {
            m_pInstance = new GstShmMgr;
        }
        return m_pInstance;
    }

    void setShmsink(QString qstrShmName, QString qstrDevice);

    void saveVideoUseShmsrc(QString qstrVideoFilename, QString qstrPath, QString qstrShmName, int nRecodeTime, int nFramerate, int nVideoWidth, int nVideoHeight);
    void mkDirs(QString dir_path);
private:
    GstShmMgr();
    ~GstShmMgr();
};

#endif // GSTSHMMGR_H
