/**
 * @file EnforcementComponentWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 단속화면을 구성하는 ui
 * @details 단속시나리오 로직도 구현되어 있다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENFORCEMENTCOMPONENTWIDGET_H
#define ENFORCEMENTCOMPONENTWIDGET_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QQueue>
#include <QSharedPointer>
#include <QFileSystemWatcher>
#include <QScopedPointer>

#include <list>
#include <vector>

#include "ConfigManager.h"
#include "SpeedUnitManager.h"
#include "camera.h"
#include "FileManager.h"
#include "HUDManager.h"
#include "StorageManager.h"
#include "base.h"
#include "v4l2_thread.h"
#include "SoundPlayer.h"

enum Mode{
    Ready,
    AT,
    Manual,
};

enum VehicleMode{
    Normal = 0,
    Truck = 1,
    MotoCycle = 2,
};

enum EnforcementMode{
    I = 0,
    A = 1,
    V = 2,
};

enum TriggerStatus{
    RELEASE,
    PRESS,
    SKIP,
};

class CustomLabel;
class FtpTransThread;
class SerialLaserManager;
class SerialViscaManager;
class Camera;
class CustomPushButton;
namespace Ui {
class EnforcementComponentWidget;
}

/**
 * @brief 단속화면을 구성하는 위젯 클래스
 * 
 */
class EnforcementComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementComponentWidget(QWidget *parent = 0);
    virtual ~EnforcementComponentWidget();
    friend class RemoteController;
    /**
     * @brief 디지털 플러스
     * 
     */
    void dzPlus();
    /**
     * @brief 디지털 마이너스
     * 
     */
    void dzMinus();

    void SaveImageVideo();
//    void SaveImageVideo(EnforcementSaveType);
    void SaveImage();
//    void SaveVideo();
    void laserInit();
    void camInit();
    void SetCamera(Camera* camera);
    void setMainMenuSize(QSize);
    void zoomRange();
    void zoomRangeMinus();
private:
    void hide(bool);
    void show(bool);
    void setOutFrame(bool isSet);
    void SetCamera();

    void hudInit();
    void hudClear();

    void doATMode();
//    void doManualMode();
    void doReadyMode();
    /**
     * @brief 캡쳐 스피드 제한값을 리턴하는 함수
     * 
     * @return float 
     */
    float GetCaptureSpeedLimit();

    /**
     * @brief 화면상에 스피드, 거리를 출력한다.
     * @param speed, distance, color, rec출력여부
     * 
     */
    void displaySpeedDistance(float, float, QColor = Qt::white, bool = false);

    /**
     * @brief 화면상에 거리를 출력한다.
     * 
     */
    void displayDistance(float);
    /**
     * @brief 화면상에 빨간색 테두리를 출력한다.
     * 
     */
    void displayRedOutline(bool);
    /**
     * @brief 썸네일 위의 스피드, 거리를 출력한다.
     * 
     */
    void displayThumbnailSpeedDistance(float, float);
    /**
     * @brief 썸네일을 출력한다.
     * 
     */
    void displayThumbnail();

/**
 * @brief hud에 스피드 거리를 출력한다.
 * 
 */
    void displayHudSpeedDistance(bool, bool, bool, bool);
    /**
     * @brief hud에 거리를 출력한다.
     * 
     */
    void displayHudDistance(bool, bool);
    /**
     * @brief 레이저 탐지 영역 설정한다.
     * 
     */
    void SetLaserDetectionAreaDistance(int);
    void zoomRangeWithoutIncrement();
    void initRec();
    /**
     * @brief Vehicle 모드에 따라 버튼 텍스트 및 테두리를 변경한다.
     * 
     */
    void setVehicleMode();
    /**
     * @brief V모드 타이머를 구동한다.
     * 
     */
    void doVModeTimer(bool);
    /**
     * @brief 단속모드 실행한다.
     * 
     */
    void doEnforceMode(bool);
    /**
     * @brief 메뉴얼 모드의 초기 동작을 수행한다.
     * 
     */
    void doPreManualMode();
    /**
     * @brief 거리 라벨을 클리어한다.
     * 
     */
    void clearDistance();
    /**
     * @brief 스피드 라벨을 클리어한다.
     * 
     */
    void clearSpeed();

    void SaveDZoomJson();
    /**
     * @brief V모드 동작시킨다.
     * 
     */
    void doVMode();

/**
 * @brief 스피드 제한을 표시한다.
 * 
 */
    void DisplaySpeedLimit(void);
//    void PushFile(QString);

public:
    SerialLaserManager* m_pSerialLaserManager = nullptr;
    SerialViscaManager* m_pSerialViscaManager = nullptr;
//    CustomPushButton* m_pReadyButton;
    void setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager);
    bool m_bNight = false;
    bool m_bVirtualMode = false;

    void setPSerialViscaManager(SerialViscaManager *newPSerialViscaManager);

private:
    bool m_bHide = false;
//    bool m_isSetOutLine = false;
    ConfigManager m_config = ConfigManager("parameter_setting1.json");
    ConfigManager m_config2 = ConfigManager("parameter_setting2.json");
    QJsonObject m_object;
    QJsonObject m_object2;
    bool m_UserModeOn;
    std::vector<QString> m_stmetervector;// = {"60", "80", "100", "120", "140", "160", "180", "200", "220", "240", "260"};
    std::vector<QString> m_ltmetervector;// = {"10~36", "30~60", "60~100", "100~160", "160~260", "260+"};
    std::vector<QString> m_stfeetvector;// = {"60", "80", "100", "120", "140", "160", "180", "200", "220", "240", "260"};
    std::vector<QString> m_ltfeetvector;// = {"10~36", "30~60", "60~100", "100~160", "160~260", "260+"};

    int m_nZoomIndex = 0;
    Camera* m_pCamera = nullptr;
    /**
     * @brief 모드를 저장하는 변수
     * 
     */
    Mode m_nMode = Ready;
    /**
     * @brief 캡쳐 스피드 행렬
     * 
     */
    QJsonArray m_captureSpeed;
    /**
     * @brief 스피드 행렬
     * 
     */
    QJsonArray m_SpeedLimit;

/**
 * @brief 비히클 모드
 * 
 */
    VehicleMode m_nVehicleMode = Normal;
    bool m_bTruckChecked = false;
    bool m_bBikeChecked = false;

    int VehicleLastId = -1;
    float m_fSpeed = 0;
    float m_fDistance = 0;

    HUDManager m_hudManager;
    EnforcementMode m_nEnforcementMode;
    bool m_bRedLine = false;
    QTimer m_VModeTimer;
    QTimer m_WhiteSpeedClearTimer;
    QTimer m_WhiteDistanceClearTimer;
//    QTimer m_ManualModeTimer;
    int m_nVModeSecond = 60;
    bool m_bVModeTimerWorking = false;
//    StorageManager m_sdcardManager;
    QPoint m_cross;
    QFileSystemWatcher m_fileSystemWatcher;
    TriggerStatus m_triggerStatus = SKIP;
    QSize m_MainMenuWidgetSize;
    FtpTransThread* m_pFtpThread = nullptr;
//    bool m_bFtpMode = false;
//    bool m_bTest = false;

    bool m_isZFWorking = false;
    CustomLabel* m_pDistanceLabel;

    QTimer m_ManualTimer;
//    QSharedPointer<QMutex> m_mutex;
//    QSharedPointer<QQueue<QString>> m_FileQueue;
protected slots:
    void on_hidePushButton_clicked();
//    void doShartAction();
    void on_zoomRangePushButton_clicked();

    void on_readyPushButton_clicked();

    void on_dzPlusPushButton_clicked();

    void on_dzMinusPushButton_clicked();
    void on_showCaptureSpeedDistance(float, float, int);
    void on_showSpeedDistance(float, float);
    void on_showDistance(float, int);
    void on_Night();
    void on_STMode();
    void on_LTMode();
    void on_EnforceModeI();
    void on_EnforceModeA();
    void on_EnforceModeV();
    void do_FileSystemWatcher(const QString&);
    void closeThread();
    void on_setNightMode(int);
    void do_FileSystemWatcherTimer();

protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:


//    void on_truckPushButton_toggled(bool checked);

//    void on_bikePushButton_toggled(bool checked);

    void on_truckPushButton_clicked();

    void on_bikePushButton_clicked();

    void on_saveImagePushButton_clicked();
    void StopHUDRec();
    void ClearSpeedDisplay();
    void ClearDistanceDisplay();
    void RestartSignal();
    void VModeVideoSave();
    void on_Show();
    void on_Hide();

    void doVModeZFControl(float fDistance, int notuse);
    void on_saveImage();
//    void on_ManualMode();
signals:
    void ShowRedOutLine(bool);
    void sig_exit();
    void sig_ATmodeOn();
    void sig_ATmodeOff();
    void push_file(QString);
private:
    Ui::EnforcementComponentWidget *ui;
};

#endif // ENFORCEMENTCOMPONENTWIDGET_H
