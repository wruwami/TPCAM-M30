#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginWidget;
//class IndicatorWidget;
class MainMenuContentWidget;
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
    void initialize();
    void finalize();
    void open_indicator_widget();
private slots:
    void on_cameraPushButton_clicked();
    void on_daynNightPushButton_clicked();
    void on_weatherPushButton_clicked();
    void on_enforcementPushButton_clicked();
    void on_speedPushButton_clicked();
    void on_wifiPushButton_clicked();
    void on_gpsPushButton_clicked();
    void on_loginWidgetClose();
    void on_dateTimeWidgetClicked();
    void on_enforcementClicked();
    void on_filemanagementClicked();
    void on_settingClicked();


private:
    Ui::MainWindow *ui;
    LoginWidget* m_pLoginWidget = nullptr;
//    IndicatorWidget* m_pIndicatorWidget;
    MainMenuContentWidget* m_pMainMenuContentWidget = nullptr;

};

#endif // MAINWINDOW_H
