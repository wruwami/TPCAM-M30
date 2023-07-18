#ifndef SERIALLASERMANAGER_H
#define SERIALLASERMANAGER_H

#include <QObject>
#include <QTimer>

#include "HeadUpDisplay.h"

class QSerialPort;
class SerialPacket;
class SerialLaserManager : public QObject
{
    Q_OBJECT
public:
    SerialLaserManager();
    virtual ~SerialLaserManager();

    QString connectLaser();
    void close();

    void start_laser();
    void request_distance(bool bRequestOn);
    void set_speed_measure_mode(unsigned char mode);
    void request_selftest();
    void set_weather_mode(unsigned char mode);
    void set_AJamming_mode(unsigned char mode);
    void set_unit(unsigned char unit);
    void set_buzzer_mode(unsigned char mode);
    void set_detection_distance(double distance);
    void set_detection_area(double area);
    void set_night_mode(unsigned char mode);
    void shutdown_laser();
    void factoryreset_laser();


    void start_virtualSpeed();
    void show_laser_info();
    void stop_laser();

    void show_camera_version();
    void show_camera_model();
    SerialPacket *getLaser_packet();

private:
    QSerialPort* m_pSerial;
    SerialPacket *laser_packet;
    int laser_con;
    CHeadUpDisplay hud;
    QTimer* m_pTimerCaptureSpeed = new QTimer(this);

protected slots:
    void serial_received();
};

#endif // SERIALLASERMANAGER_H
