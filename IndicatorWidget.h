#ifndef INDICATORCAMERAWIDGET_H
#define INDICATORCAMERAWIDGET_H

#include <QDialog>

class CustomPushButton;
namespace Ui {
class IndicatorWidget;
}

class IndicatorWidget : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorWidget(QWidget *parent = 0);
    ~IndicatorWidget();
private:
    void clearSecondRow();
private slots:
    void on_cameraPushButton_clicked();

    void on_screenRecordingPushButton_clicked();

    void on_daynNightPushButton_clicked();

    void on_gpsPushButton_clicked();

    void on_comPushButton_clicked();

    void on_speedPushButton_clicked();

    void on_enforcementPushButton_clicked();

    void on_weatherPushButton_clicked();
    void on_cameraExposeClicked();
    void on_cameraForcusClicked();

private:
    Ui::IndicatorWidget *ui;
    CustomPushButton* m_pCameraFocusPushButton;
    CustomPushButton* m_pCameraExposePushButton;

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
};

#endif // INDICATORCAMERAWIDGET_H
