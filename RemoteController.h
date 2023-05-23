#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

//#include <QQueue>
#include <QObject>

class MainWindow;
class RemoteController
{
public:
    RemoteController(MainWindow *parent = nullptr);
    int Start();
    void CreateThread();
private:
    MainWindow* m_pMainwindow;
//    QQueue<int> m_queue;
};

#endif // REMOTECONTROLLER_H
