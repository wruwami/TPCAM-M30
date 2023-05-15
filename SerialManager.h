#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QElapsedTimer>

class QSerialPort;
class SerialManager : public QObject
{
    Q_OBJECT
public:
    SerialManager(QObject *parent = nullptr);
    void serial_connect();
private:
    int con;
    int m_nTTFF=0;
    int m_nTTFFFlag = 0;
    QElapsedTimer m_timer;

private:
    QSerialPort* m_pSerial;
protected slots:
    void connected();
    void serial_received();
};

#endif // SERIALMANAGER_H
