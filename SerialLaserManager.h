/**
 * @file SerialLaserManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief 레이저 시리얼 통신 관리 클래스
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SERIALLASERMANAGER_H
#define SERIALLASERMANAGER_H

#include <QObject>
#include <QTimer>
#include <QMutex>

#include "HeadUpDisplay.h"

class QSerialPort;
class SerialPacket;
class SerialLaserManager : public QObject
{
    Q_OBJECT
public:
    SerialLaserManager();
    virtual ~SerialLaserManager();
private:
    QString connectLaser();
    void close();
public:
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
    void stop_virtualSpeed();
    void show_laser_info();
    void stop_laser();

    SerialPacket *getLaser_packet();
    void SetLaserDetectionAreaDistance(int, bool);
private:
    QSerialPort* m_pSerial;
    SerialPacket *laser_packet;
    int laser_con;
    CHeadUpDisplay hud;
    QTimer* m_pTimerCaptureSpeed = new QTimer(this);
    QMutex m_writeMutex;

protected slots:
    void serial_received();
};

#endif // SERIALLASERMANAGER_H
