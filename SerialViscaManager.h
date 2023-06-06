#ifndef SERIALVISCAMANAGER_H
#define SERIALVISCAMANAGER_H

#include <QObject>
#include <QElapsedTimer>

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
    QSerialPort* serial_visca;
    ViscaPacket *visca_packet;
    int camera_con;
    QString number;
    QString snr;
    int snr_ary[7];
    int con;

    //cnrk
    //추가
//    CHeadUpDisplay hud;

    QString m_gmt;

    QElapsedTimer m_timer;
    int m_nTTFF=0;
    int m_nTTFFFlag = 0;

    QString m_zoom_pqrs;
    QString m_Dzoom_pqrs;
    QString m_focus_pqrs;
    QString m_shutter_pq;
    QString m_gain_pq;
    QString m_iris_pq;


public:
    void show_camera_version();
    void show_camera_model();

    void set_infrared_mode_on();
    void set_infrared_mode_off();
    void set_infrared_mode_auto();

    void set_noise_reduction_on(QString p);

    void set_defog_off();
    void set_defog_on();
    QString change_defog_mode();

    void set_DIS_off();
    void set_DIS_on();

    void set_HLC_off();
    void set_HLC_on();

    void zoom(int index);
    void plus_zoom();
    void minus_zoom();

    void dzoom(int currentIndex);
    void plus_dzoom();
    void minus_dzoom();

    void set_focus(QString a_pqrs);
    void plus_focus();
    void minus_focus();

    void separate_zoom_mode();
    void combine_zoom_mode();

    void set_manual_focus();
    void set_auto_focus();
    void set_AF_one_push_trigger();

    void set_AE_shutter_priority();
    void set_AE_manual();

    void read_AE_mode();

    void set_shutter_speed(int currentIndex);
    void set_gain(int currentIndex);
    void set_iris(int currentIndex);

    void read_shutter_speed();
    void read_gain();
    void read_iris();

    void set_IRCorrection_standard();
    void set_IRCorrection_IRlight();

    //inquiry
    void show_wideDynamicMode();
    void show_DISMode();
    void show_IRCorrection();
    void show_AFMode();
    void show_ICR_OnOff();
    void show_AutoICR();
    void show_WBMode();
    void show_AEMode();
    void show_focusPosition();
    void show_focusMode();
    void show_zoomPosition();
    void show_dzoomOnOff();
    void show_dzoomPosition();
    void show_dZoomMode();
    void show_noiseReduction();

public slots:
    void receive_camera();

};

#endif // SERIALVISCAMANAGER_H
