#ifndef CAMERAALIGNWIDGET_H
#define CAMERAALIGNWIDGET_H

#include <QWidget>
#include <QPoint>

#include "ConfigManager.h"

enum AlignMode{
    HUD,
    Laser,
};

enum DefaultHUDValue {
    HUD_x = 6,
    HUD_y = 6,
};

enum DefaultLaserValue {
    Laser_x = 960,
    Laser_y = 540,
};

class Camera;
class CustomPushButton;
class SerialLaserManager;
namespace Ui {
class CameraAlignWidget;
}

class CameraAlignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraAlignWidget(QWidget *parent = 0);
    ~CameraAlignWidget();
    void SetCamera(Camera* caemera);
private:
    void SetHudMode();
    void SetLaserMode();
    void SetDirection(int, int);
public:
    CustomPushButton* m_pHomeButton;
    CustomPushButton* m_pSaveButton;
    CustomPushButton* m_pCancelButton;
private:
    bool m_bHUDChecked = true;
    bool m_bCameraChecked = false;
    ConfigManager m_configManager = ConfigManager("setting_reticle.json");
    QJsonObject m_object;
    QPoint m_HUDPoint;
    QPoint m_LaserPoint;
    AlignMode m_nMode = HUD;
    SerialLaserManager* m_pSerialLaserManager = nullptr;
private slots:
    void on_hudPushButton_clicked();

    void on_cameraPushButton_clicked();

    void on_leftPushButton_clicked();

    void on_rightPushButton_clicked();

    void on_savePushButton_clicked();

    void on_downPushButton_clicked();

    void on_defaultPushButton_clicked();

    void on_upPushButton_clicked();

    void on_autoTriggerPushButton_toggled(bool checked);
    void on_showDistance(float,int);

private:
    Ui::CameraAlignWidget *ui;
    Camera* m_pCamera;
};

#endif // CAMERAALIGNWIDGET_H
