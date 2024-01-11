/**
 * @file SerialGPSManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief GPS 시리얼 통신 관리 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SERIALGPSMANAGER_H
#define SERIALGPSMANAGER_H

#include <QObject>
#include <QElapsedTimer>
#include <QDateTime>

class QSerialPort;
/**
 * @brief GPS 시리얼 통신 관리 클래스
 * 
 */
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
    QString GetDateTimeString();
    QDateTime GetDateTime();
    int GetSatellitesInView();
    QString GetLatitude();
    QString GetLongitude();
    float GetLatitudeValue();
    float GetLongitudeValue();

    QString GetSensitivity();
    QString changeMinuteToDegree(QString Minute);
private:
    int con = 0;
    int m_nTTFF=0;
    int m_nTTFFFlag = 0;
    QElapsedTimer m_timer;
    int m_nSatellitesInView = 0;
    QDateTime m_DateTime;
    QString m_Latitude = "N000.000000";
    QString m_Longitude = "E000.000000";
    QString m_sensitivity;
    float m_fLongitude = 0;
    float m_fLatitude = 0;
    bool m_bFirstLog = true;

private:
    QSerialPort* m_pSerial;
protected slots:
    void serial_received();
};

static QString GetLatitude()
{
    return SerialGPSManager::GetInstance()->GetLatitude();
}
static QString GetLongitude()
{
    return SerialGPSManager::GetInstance()->GetLongitude();
}


#endif // SERIALGPSMANAGER_H
