/**
 * @file MainWindow.h
 * @author wruwami (wruwami@naver.com)
 * @brief 어플리케이션 바탕 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ltc2943.h"
#include "SoundPlayer.h"


enum WidgetType
{
    Login,
    Setting,
    Enforcement,
    FileManager,
    MainMenu,
    CameraAlign,
    Other,
};

class Camera;
class IndicatorCameraExposeWidget;
class IndicatorCameraFocusWidget;
class CameraAlignWidget;
class DateTimeWidget;
class LoginWidget;
class MainMenuWidget;
class IndicatorDialog;
class MainMenuContentWidget;
class MainMenuAdminAlignWidget;
class FileManagerWidget;
class RemoteController;
class EnforcementWidget;
class CustomLabel;
class CustomPushButton;
class screensaver;
class SerialLaserManager;
class SerialViscaManager;
namespace Ui {
class MainWindow;
}

/**
 * @brief 어플리케이션 바탕 위젯 클래스
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(screensaver* screensaver, QWidget *parent = 0);
    ~MainWindow();
    friend class RemoteController;
    void get(screensaver *f);
private:
/**
 * @brief 메인메뉴 초기화 함수
 * 
 */
    void initializeMainMenuWidget();
/**
 * @brief 로그인 위젯 초기화 함수
 * 
 */
    void initializeLoginWidget();
    void finalize();
/**
 * @brief 인디케이터 창 보여주는 함수
 * 
 */
    void open_indicator_widget();
    void removeseconditem();
    void removeseconditem(QWidget*&);
/**
 * @brief 인디케이터 창 보여주는 함수(파라미터를 통해 선택)
 *
 */
    void showIndicator(bool);
    void SetWindowWarningMode();
    void OpenEnforcement();
    void OpenFileManagement();
    void OpenMainMenu();
/**
 * @brief 배터리 퍼센트 체크 함수
 * 
 */
    void CheckBatteryPercent();
/**
 * @brief 베터리 차징 여부 체크 함수
 * 
 */
    void CheckBatteryCharge();
    void SelfTestFail(bool = false);
/**
 * @brief 파워 오프 함수
 * 
 */
    void PowerOff();
/**
 * @brief expired_date.txt 체크하여 로그인 만료를 체크하는 함수
 * 
 */
    void CheckLoginExpired();
/**
 * @brief 파워 세이빙 타임을 체크하는 함수
 * 
 */
    void CheckPowerSavingTime();
    void SetPowerSavingMode(bool);
/**
 * @brief 배터리 초기화 함수
 * 
 */
    void BatteryInit();
    void ChechMainMenuImage();
/**
 * @brief 카메라 영상 위젯을 세팅하는 함수
 * 
 */
    void SetCamera();
/**
 * @brief 단속화면에서 적발 시 빨간색을 그리는 함수
 * 
 */
    void SetRedLine();
private slots:
    void on_cameraPushButton_clicked();
    void on_daynNightPushButton_clicked();
    void on_weatherPushButton_clicked();
    void on_enforcementPushButton_clicked();
    void on_speedPushButton_clicked();
    void on_wifiPushButton_clicked();
    void on_gpsPushButton_clicked();
    void on_loginWidgetClicked();
    void on_dateTimeWidgetClicked();
    void on_enforcementClicked();
    void on_filemanagementClicked();
    void on_settingClicked();
//    void on_mainMenuTitlePushButton_clicked();
    void on_device_id_clicked();
    void on_camera_align_clicked();
    void on_camera_zoom_focus();
    void on_SettingSaveClicked();
    void on_SettingCancelClicked();
    void on_DateTimeSaveClicked();
    void on_DateTimeCancelClicked();
    void on_mainMenuHomeClicked();
    void on_logo_clicked();
    void on_userNameChanged(QString arg);
    void on_DeviceIdSaveClicked();
    void on_DeviceIdCancelClicked();
    void on_ShowRedOutLine(bool);
    void on_screenShot();
private:
    Ui::MainWindow *ui;
    DateTimeWidget* m_pDateTimeWidget = nullptr;
    LoginWidget* m_pLoginWidget = nullptr;
    MainMenuWidget* m_pMainMenuWidget = nullptr;
    IndicatorDialog* m_pIndicatorWidget = nullptr;
    MainMenuContentWidget* m_pMainMenuContentWidget = nullptr;
    MainMenuAdminAlignWidget* m_pMainMenuAdminAlignWidget = nullptr;
    CameraAlignWidget* m_pCameraAlignWidget = nullptr;
    RemoteController* m_pRemoteController = nullptr;
    EnforcementWidget* m_pEnforcementWidget = nullptr;
    CustomLabel* m_pBatteryStatus;
    QToolButton* m_pBatteryPercent;
    Camera* m_pCamera = nullptr;
    LTC2943 ltc = LTC2943(15);
    WidgetType m_widgetType = Other;
   /**
    * @brief 현재 사용하는 유저 네임 변수
    * 
    */
    QString m_userName;
    QWidget* m_redAlertWidget = nullptr;
   /**
    * @brief 100 ms 타이머
    * 
    */
    QTimer* m_p100msTimer;
/**
 * @brief 500 ms 타이머
 * 
 */
    QTimer* m_p500msTimer;
    bool m_bFlick = false;
/**
 * @brief 파워 세이빙 타임(분)
 * 
 */
    int m_nPowerSavingMinute = 0;
    screensaver *m_screensaver;
/**
 * @brief 셀프 테스트 실패 여부 변수
 * 
 */
    bool m_bSelfTestFailed = false;
    SerialLaserManager* m_pSerialLaserManager = nullptr;
    SerialViscaManager* m_pSerialViscaManager = nullptr;
    //    Language m_mLanguage = Language::English;
    bool m_bRedLine = false;
    int m_nLogCount= 0;
    QSize m_MainMenuWidgetSize;
/**
 * @brief 스크린 레코딩 파일 네임 변수
 * 
 */
    QString m_srFileFullName;
/**
 * @brief 현재 날짜 변수
 * 
 */
    QDate m_date;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void showEvent(QShowEvent* event);
protected slots:
/**
 * @brief 리모트 1번 기능
 * 
 */
    void doFirstAction();
    /**
 * @brief 리모트 2번 기능
 * 
 */
    void doSecondAction();
    /**
 * @brief 리모트 3번 기능
 * 
 */
    void doThirdAction();
    /**
 * @brief 리모트 4번 기능
 * 
 */
    void doForthAction();
    /**
 * @brief 리모트 5번 기능
 * 
 */
    void do5thAction();
    /**
 * @brief 리모트 #번 기능
 * 
 */
    void doSharpAction();
    /**
 * @brief 리모트 *번 기능
 * 
 */
    void doStarAction();

    /**
 * @brief 리모트 0 기능
 * 
 */
    void doZeroAction();
    /**
 * @brief 리모트 9번 기능
 * 
 */
    void do9thAction();
    void OnTimer100msFunc();
    void OnTimer500msFunc();
    void afterWindowShown();
    void on_SystemInfoClicked();
};

#endif // MAINWINDOW_H
