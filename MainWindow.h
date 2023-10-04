#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ltc2943.h"


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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(screensaver* screensaver, QWidget *parent = 0);
    ~MainWindow();
    friend class RemoteController;
    void get(screensaver *f);
private:
    void initializeMainMenuWidget();
    void initializeLoginWidget();
    void finalize();
    void open_indicator_widget();
    void removeseconditem();
    void removeseconditem(QWidget*&);
    void showIndicator(bool);
    void setWarningMode();
    void SetWindowWarningMode();
    void OpenEnforcement();
    void OpenFileManagement();
    void OpenMainMenu();
    void CheckBatteryPercent();
    void CheckBatteryCharge();
    void SelfTestFail(bool = false);
    void PowerOff();
    void CheckLoginExpired();
    void CheckPowerSavingTime();
    void SetPowerSavingMode(bool);
    void BatteryInit();
    void ChechMainMenuImage();
    void SetCamera();
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
    void on_datetimeChecked();
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
    QString m_userName;
    int m_nFailTimerId;
    bool m_bLoginFail = false;
    QWidget* m_redAlertWidget = nullptr;
    QTimer* m_p100msTimer;
    QTimer* m_p500msTimer;
    bool m_bFlick = false;
    int m_nPowerSavingMinute = 0;
    int m_nCheckSecond = 0;
    bool m_bPowerSavingMode = false;
    int m_nPowerOffSecond = 0;
    int sec = 0;
    screensaver *m_screensaver;
    bool m_bSelfTestFailed = false;
    SerialLaserManager* m_pSerialLaserManager = nullptr;
    SerialViscaManager* m_pSerialViscaManager = nullptr;
    int m_nCrackDownCount;
    //    Language m_mLanguage = Language::English;
    bool m_bRedLine = false;
    int m_nLogCount= 0;
    QSize m_MainMenuWidgetSize;
    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void showEvent(QShowEvent* event);
protected slots:
    void doFirstAction();
    void doSecondAction();
    void doThirdAction();
    void doForthAction();
    void do5thAction();
    void doSharpAction();
    void doStarAction();
    void doZeroAction();
    void do9thAction();
    void OnTimer100msFunc();
    void OnTimer500msFunc();
    void afterWindowShown();
    void on_SystemInfoClicked();
};

#endif // MAINWINDOW_H
