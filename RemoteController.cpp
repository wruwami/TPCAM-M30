#include "RemoteController.h"

#include <QThread>

#include "RemoteControlWorker.h"
#include "MainWindow.h"

RemoteController::RemoteController(MainWindow *parent)
{
    m_pMainwindow = parent;
}

int RemoteController::Start()
{

}

void RemoteController::CreateThread()
{
    QThread thread;

    RemoteControlWorker *worker = new RemoteControlWorker(m_pMainwindow);
    worker->moveToThread(&thread);
    thread.start();

    QObject::connect(worker, &RemoteControlWorker::start, worker, &RemoteControlWorker::doWork);
    QObject::connect(&thread, &QThread::finished, worker, &QObject::deleteLater);

    QObject::connect(worker, &RemoteControlWorker::resultReady, [&](const QString &result){
        //            qDebug() << result;
        thread.quit(); // 스레드중지
    });

    emit worker->start("World");

}
