#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

//#include <QQueue>

class RemoteController
{
public:
    RemoteController();
    int Start();
    void CreateThread();
private:
//    QQueue<int> m_queue;
};

#endif // REMOTECONTROLLER_H
