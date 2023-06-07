#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>

class QSpacerItem;
class CustomLabel;
class CustomPushButton;
class HomeButtonWidget;
class QToolButton;
namespace Ui {
class MainMenuWidget;
}

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = 0);
    ~MainMenuWidget();
    void setMainMenuTitle(QString title);
    void setMainMenuImage(QString path_name, QString file_name);
    void enableButtons(bool enable);
    void updateStretch();
    void showIndicator(bool = true);
    void setBatteryPercentValue(int);

public:
    CustomPushButton* m_pHomePushButton;
private:
    Ui::MainMenuWidget *ui;
    CustomLabel* m_pHomeTitleLabel;
    HomeButtonWidget* m_pHomeButtonWidget;
    QSpacerItem* m_pSpacerItem;
public:
    CustomPushButton* m_pCameraPushbutton;
    CustomPushButton* m_pDaynNightPushbutton;
    CustomPushButton* m_pWeatherPushbutton;
    CustomPushButton* m_pEnforcementPushbutton;
    CustomPushButton* m_pSpeedPushbutton;
    CustomPushButton* m_pWifiPushbutton;
    CustomPushButton* m_pGpsPushbutton;
    CustomPushButton* m_pMainMenuTitlePushButton;
    CustomLabel* m_pBatteryChargingLabel;
    QToolButton* m_pBatteryPercentButton;


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
