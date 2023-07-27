#ifndef SERIALVISCAMANAGER_H
#define SERIALVISCAMANAGER_H

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>
#include <QJsonObject>


class QSerialPort;
class ViscaPacket;
class SerialViscaManager : public QObject
{
    Q_OBJECT
public:
    SerialViscaManager();
    virtual ~SerialViscaManager();
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

    QTimer* m_pTimerInquiryZoom = new QTimer(this);
    QTimer* m_pTimerInquiryFocus = new QTimer(this);
    QTimer* m_pTimerInquiryIris = new QTimer(this);
public:
    void show_camera_version();
    void show_camera_model();

    void set_infrared_mode_on();
    void set_infrared_mode_off();
    void set_infrared_mode_auto();

    void set_noise_reduction_on(QString p); // DNR

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
    void zoom_from_pqrs(QString pqrs_input);
    void dzoom_from_pq(QString pq_input);

    void dzoom(int currentIndex);
    void plus_dzoom();
    void minus_dzoom();

    void set_focus(QString a_pqrs);
    void plus_focus();
    void minus_focus();
    void focus_from_pqrs(QString pqrs_input);


    void separate_zoom_mode();
    void combine_zoom_mode();

    void set_manual_focus();
    void set_auto_focus();
    void set_AF_one_push_trigger();

    void set_AE_shutter_priority();
    void set_AE_manual();

    void read_AE_mode();

    void set_shutter_speed(int currentIndex);
    void set_shutter_speed_from_pq(QString pq_input);
    void set_gain(int currentIndex);
    void set_gain_from_pq(QString pq_input);
    void set_iris(int currentIndex);
    void set_iris_from_pq(QString pq_input);

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

    void SetDayMode(int index);
    void SetDayMode(QJsonObject object);

    ViscaPacket *getVisca_packet() const;
signals:
    void sig_pb_zoom_clicked();
    void sig_pb_focus_clicked();
    void sig_pb_shutter_clicked();
    void sig_pb_iris_clicked();


public slots:
    void receive_camera();
    void get_inquiry_zoom();
    void get_inquiry_focus();
    void get_inquiry_iris();
    void on_show_dzoom(QString);
    void on_show_focus(QString);
};

#endif // SERIALVISCAMANAGER_H
