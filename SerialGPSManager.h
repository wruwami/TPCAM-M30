#ifndef SERIALGPSMANAGER_H
#define SERIALGPSMANAGER_H

#include <QObject>
#include <QElapsedTimer>
#include <QDateTime>

class QSerialPort;
class SerialGPSManager : public QObject
{
    Q_OBJECT
public:
//    SerialGPSManager(QObject *parent = nullptr);
    SerialGPSManager();
    SerialGPSManager(const SerialGPSManager& other);
    ~SerialGPSManager() {}
    static SerialGPSManager* instance;
public:
    static SerialGPSManager* GetInstance()
    {
        if(instance == nullptr) instance = new SerialGPSManager();
        return instance;
    }

    void serial_connect();
    QDateTime GetDateTime();
    int GetSatellitesInView();
    QString GetLatitude();
    QString GetLongitude();
private:
    int con;
    int m_nTTFF=0;
    int m_nTTFFFlag = 0;
    QElapsedTimer m_timer;
    int m_nSatellitesInView = 0;
    QDateTime m_DateTime;
    QString m_Latitude;
    QString m_Longitude;
    QString m_sensitivity;

private:
    QSerialPort* m_pSerial;
protected slots:
    void serial_received();
};

#endif // SERIALGPSMANAGER_H
