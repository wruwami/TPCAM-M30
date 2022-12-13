#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CameraAlignWidget;
class DateTimeWidget;
class LoginWidget;
class MainMenuWidget;
class IndicatorDialog;
class MainMenuContentWidget;
class MainMenuAdminAlignWidget;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void initializeMainMenuWidget();
    void initializeLoginWidget();
    void finalize();
    void open_indicator_widget();
    void removeseconditem();
    void showIndicator(bool);
    void setWarningMode();
    void SetWindowWarningMode();
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

private:
    Ui::MainWindow *ui;
    DateTimeWidget* m_pDateTimeWidget = nullptr;
    LoginWidget* m_pLoginWidget = nullptr;
    MainMenuWidget* m_pMainMenuWidget = nullptr;
    IndicatorDialog* m_pIndicatorWidget = nullptr;
    MainMenuContentWidget* m_pMainMenuContentWidget = nullptr;
    MainMenuAdminAlignWidget* m_pMainMenuAdminAlignWidget = nullptr;
    CameraAlignWidget* m_pCameraAlignWidget = nullptr;
    QString m_userName;
    int m_nFailTimerId;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
