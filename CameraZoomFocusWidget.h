#ifndef CAMERAZOOMFOCUSWIDGET_H
#define CAMERAZOOMFOCUSWIDGET_H

#include <QWidget>
#include "SerialViscaManager.h"

class Camera;
class SerialLaserManager;
namespace Ui {
class CameraZoomFocusWidget;
}

class CameraZoomFocusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraZoomFocusWidget(QWidget *parent = 0);
    ~CameraZoomFocusWidget();
    void SetCamera(Camera* camera);
private:
    void ZoomRange();
    void SetLaserDetectionAreaDistance(int zoom_index);
private slots:
    void on_optPushButton_clicked();

    void on_focusPlusPushButton_clicked();

    void on_FocusMinusPushButton_clicked();

    void on_autoTriggerPushButton_clicked();

    void on_dayComboBox_currentIndexChanged(int index);

    void on_initPushButton_clicked();

    void on_zoomRangePushButton_clicked();

    void on_dzPlusPushButton_clicked();

    void on_dzMinusPushButton_clicked();

    void on_showDistance(float,int);
private:
    Ui::CameraZoomFocusWidget *ui;
    SerialViscaManager m_serialViscaManager;
    Camera* m_pCamera;
    size_t m_nLtIndex = 2;
    size_t m_nStIndex = 3;
    SerialLaserManager* m_pSerialLaserManager = nullptr;
    bool m_UserModeOn;
    std::vector<QString> m_stmetervector;// = {"60", "80", "100", "120", "140", "160", "180", "200", "220", "240", "260"};
    std::vector<QString> m_ltmetervector;// = {"10~36", "30~60", "60~100", "100~160", "160~260", "260+"};
    std::vector<QString> m_stfeetvector;// = {"60", "80", "100", "120", "140", "160", "180", "200", "220", "240", "260"};
    std::vector<QString> m_ltfeetvector;// = {"10~36", "30~60", "60~100", "100~160", "160~260", "260+"};

};

#endif // CAMERAZOOMFOCUSWIDGET_H
