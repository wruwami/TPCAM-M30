/**
 * @file CameraAlignWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief admin-align유저가 laser, hud align 기능을 수행할 수 있는 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CAMERAALIGNWIDGET_H
#define CAMERAALIGNWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QTimer>

#include "ConfigManager.h"
#include "HUDManager.h"
#include "base.h"

enum AlignMode{
    HUD,
    Laser,
};

class Camera;
class CustomLabel;
class CustomPushButton;
class SerialLaserManager;
namespace Ui {
class CameraAlignWidget;
}

/**
 * @brief admin-align유저가 laser, hud align 기능을 수행할 수 있는 위젯 클래스
 * 
 */
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
//    void SetLaserMode2();
    void SetDirection(int, int);
public:
    CustomPushButton* m_pHomeButton;
    CustomPushButton* m_pSaveButton;
    CustomPushButton* m_pCancelButton;
    void setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager);

private:
    bool m_bHUDChecked = true;
    bool m_bCameraChecked = true;
    ConfigManager m_configManager = ConfigManager("setting_reticle.json");
    QJsonObject m_object;
    QPoint m_HUDPoint;
    QPoint m_LaserPoint;
    AlignMode m_nMode = HUD;
    SerialLaserManager* m_pSerialLaserManager = nullptr;
    int m_CameraMoveUnit = 1;
    QTimer m_ClearTimer;
    CustomLabel* m_pSpeedSensitivitylabel;
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

    void ClearDisplay();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent* event);

private:
    Ui::CameraAlignWidget *ui;
    Camera* m_pCamera;
    HUDManager m_hud;
};

#endif // CAMERAALIGNWIDGET_H
