#ifndef SERIALLASERMANAGER_H
#define SERIALLASERMANAGER_H

#include <QObject>

class QSerialPort;
class SerialPacket;
class SerialLaserManager : public QObject
{
    Q_OBJECT
public:
    SerialLaserManager();
    QString connectLaser();
    void close();
private:
    QSerialPort* m_pSerial;
    SerialPacket *laser_packet;
    int laser_con;
protected:
    void serial_received();
};

#endif // SERIALLASERMANAGER_H
