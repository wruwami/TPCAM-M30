#ifndef INDICATORCAMERADIALOG_H
#define INDICATORCAMERADIALOG_H

#include <QDialog>

#include "SerialViscaManager.h"
#include "ConfigManager.h"

class CustomPushButton;
class IndicatorCameraExposeWidget;
class IndicatorCameraFocusWidget;
namespace Ui {
class IndicatorDialog;
}

class IndicatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorDialog(QWidget *parent = 0);
    ~IndicatorDialog();
    void setFocusExposeDisabled(bool = false);
    bool GetGPSStatus();
    bool GetWifiStatus();
private:
    void clearSecondRow();
private slots:
    void on_cameraPushButton_clicked();



    void on_daynNightPushButton_clicked();

    void on_gpsPushButton_clicked();

    void on_comPushButton_clicked();

    void on_speedPushButton_clicked();

    void on_enforcementPushButton_clicked();

    void on_weatherPushButton_clicked();
    void on_cameraExposeClicked();
    void on_cameraFocusClicked();

    void on_pushButton_clicked();
    void on_screenRecordingPushButton_clicked();
    void on_screenCapturePushButton_clicked();
    void on_day1WidgetClicked();
    void on_day2WidgetClicked();
    void on_day3WidgetClicked();
    void on_night1WidgetClicked();
    void on_night2WidgetClicked();
    void on_night3WidgetClicked();
public:
    CustomPushButton* m_pCameraFocusPushButton = nullptr;
    CustomPushButton* m_pCameraExposePushButton = nullptr;
    bool m_bFocusExposeDisabled = true;
private:
    Ui::IndicatorDialog *ui;
    CustomPushButton* m_pDay1PushButton;
    CustomPushButton* m_pDay2PushButton;
    CustomPushButton* m_pDay3PushButton;
    CustomPushButton* m_pNight1PushButton;
    CustomPushButton* m_pNight2PushButton;
    CustomPushButton* m_pNight3PushButton;

    CustomPushButton* m_pSunnyPushButton;
    CustomPushButton* m_pRainyPushButton;
    CustomPushButton* m_pImagePushButton;
    CustomPushButton* m_pImageVideoPushButton;
    CustomPushButton* m_pVideoPushButton;
    CustomPushButton* m_pSTPushButton;
    CustomPushButton* m_pLTPushButton;
    CustomPushButton* m_pWifiPushButton;
    CustomPushButton* m_pBTPushButton;
    CustomPushButton* m_pEthernetPushButton;
    SerialViscaManager m_serialViscaManager;
    ConfigManager m_configManager = ConfigManager("exposure.json");
    QJsonObject m_jsonObject;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    bool m_isRecording = false;
};

#endif // INDICATORCAMERADIALOG_H
