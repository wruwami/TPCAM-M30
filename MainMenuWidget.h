#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class MainMenuWidget;
}

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = 0);
    ~MainMenuWidget();
    void SetMainMenuTitle(QString title);
    void enableButtons(bool enable);
private:
    Ui::MainMenuWidget *ui;

public:
    CustomPushButton* m_pCameraPushbutton;
    CustomPushButton* m_pDaynNightPushbutton;
    CustomPushButton* m_pWeatherPushbutton;
    CustomPushButton* m_pEnforcementPushbutton;
    CustomPushButton* m_pSpeedPushbutton;
    CustomPushButton* m_pWifiPushbutton;
    CustomPushButton* m_pGpsPushbutton;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
//private slots:
//    void on_cameraPushButton_clicked();
//    void on_daynNightPushButton_clicked();
//    void on_weatherPushButton_clicked();
//    void on_enforcementPushButton_clicked();
//    void on_speedPushButton_clicked();
//    void on_wifiPushButton_clicked();
//    void on_gpsPushButton_clicked();
};

#endif // MAINMENUWIDGET_H
