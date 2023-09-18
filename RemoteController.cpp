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

    m_thread.reset(new QThread);
    RemoteControlWorker *worker = new RemoteControlWorker(m_pMainwindow);
    worker->moveToThread(m_thread.data());
    m_thread->start();

    QObject::connect(worker, &RemoteControlWorker::start, worker, &RemoteControlWorker::doWork);
    QObject::connect(worker, &RemoteControlWorker::FirstAction, m_pMainwindow, &MainWindow::doFirstAction);
    QObject::connect(worker, &RemoteControlWorker::SecondAction, m_pMainwindow, &MainWindow::doSecondAction);
    QObject::connect(worker, &RemoteControlWorker::SharpAction, m_pMainwindow, &MainWindow::doSharpAction);
    QObject::connect(worker, &RemoteControlWorker::ThirdAction, m_pMainwindow, &MainWindow::doThirdAction);
    QObject::connect(worker, &RemoteControlWorker::ForthAction, m_pMainwindow, &MainWindow::doForthAction);
    QObject::connect(worker, &RemoteControlWorker::FifththAction, m_pMainwindow, &MainWindow::do5thAction);
    QObject::connect(worker, &RemoteControlWorker::NinethAction, m_pMainwindow, &MainWindow::do9thAction);
    QObject::connect(worker, &RemoteControlWorker::ZeroAction, m_pMainwindow, &MainWindow::doZeroAction);
    QObject::connect(worker, &RemoteControlWorker::StarAction, m_pMainwindow, &MainWindow::doStarAction);

    QObject::connect(m_thread.data(), &QThread::finished, worker, &QObject::deleteLater);

    QObject::connect(worker, &RemoteControlWorker::resultReady, [&](const QString &result){
        //            qDebug() << result;
        m_thread->quit(); // 스레드중지
    });

    emit worker->start(m_pMainwindow);

}
