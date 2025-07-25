/**
 * @file MainMenuWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 화면 상단 메인메뉴를 구성하는 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

/**
 * @brief 화면 상단 메인메뉴를 구성하는 위젯 클래스
 * 
 */
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
    void setBatteryCharge(bool);
    void setIndicatorImage(CustomPushButton*, QString, QString);
    void setTransparentBackGround(bool);
    void hideButton();
    void setRedLine(bool);
private:
    void initImage();
private slots:
    void DisableAllButton();
    void EnableAllButton();
public:
    CustomPushButton* m_pHomePushButton;
private:
    Ui::MainMenuWidget *ui;
    CustomLabel* m_pHomeTitleLabel;
    HomeButtonWidget* m_pHomeButtonWidget;
    bool m_bRedLine = false;
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
    void paintEvent(QPaintEvent *event);
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
