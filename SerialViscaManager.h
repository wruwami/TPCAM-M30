#ifndef SERIALVISCAMANAGER_H
#define SERIALVISCAMANAGER_H

#include <QObject>

class QSerialPort;
class ViscaPacket;
class SerialViscaManager : public QObject
{
    Q_OBJECT
public:
    SerialViscaManager();
    QString connectVisca();
    void close();
private:
    QSerialPort* m_pSerial;
    ViscaPacket *visca_packet;
    int camera_con;
protected:
    void receive_camera();

};

#endif // SERIALVISCAMANAGER_H
