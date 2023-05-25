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

    m_thread = new QThread;
    RemoteControlWorker *worker = new RemoteControlWorker(m_pMainwindow);
    worker->moveToThread(m_thread);
    m_thread->start();

    QObject::connect(worker, &RemoteControlWorker::start, worker, &RemoteControlWorker::doWork);
    QObject::connect(worker, &RemoteControlWorker::FirstAction, m_pMainwindow, &MainWindow::doFirstAction);
    QObject::connect(m_thread, &QThread::finished, worker, &QObject::deleteLater);

    QObject::connect(worker, &RemoteControlWorker::resultReady, [&](const QString &result){
        //            qDebug() << result;
        m_thread->quit(); // 스레드중지
    });

    emit worker->start(m_pMainwindow);

}
