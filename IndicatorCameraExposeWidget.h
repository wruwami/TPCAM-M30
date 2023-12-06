/**
 * @file IndicatorCameraExposeWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 인디케이터 카메라에서 노출에 해당하는 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INDICATORCAMERAEXPOSEWIDGET_H
#define INDICATORCAMERAEXPOSEWIDGET_H

#include <QWidget>
#include <QDialog>

#include "SerialViscaManager.h"

namespace Ui {
class IndicatorCameraExposeWidget;
}

class IndicatorCameraExposeWidget : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorCameraExposeWidget(QWidget *parent = 0);
    ~IndicatorCameraExposeWidget();
    void timerEvent(QTimerEvent *event);

private:
    Ui::IndicatorCameraExposeWidget *ui;
    bool m_bHide = false;
    SerialViscaManager* m_serialViscaManager;
    bool m_bDNR = false;
    bool m_bDIS = false;
    bool m_bDEFOG = false;
    bool m_bHLC = false;
    std::map<std::string, int> m_gainMap;
    std::map<std::string, int> m_gain_fullMap;
    std::map<std::string, int> m_irisMap;
    std::map<std::string, int> m_iris_fullMap;
    std::map<std::string, int> m_shutterSpeedMap;

    std::vector<std::pair<std::string, int>> m_gainVec;
    std::vector<std::pair<std::string, int>> m_gain_fullVec;
    std::vector<std::pair<std::string, int>> m_irisVec;
    std::vector<std::pair<std::string, int>> m_iris_fullVec;
    std::vector<std::pair<std::string, int>> m_shutterSpeedVec;

    QMutex m_mutex;
    bool m_bIsConstructionFinished = false;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_showHidePushButton_clicked();
    void on_speedPushButton_clicked();
    void on_hlcOnPushButton_clicked();
    void on_defogOffPushButton_clicked();
    void on_disOffPushButton_clicked();
    void on_daynNightComboBox_currentIndexChanged(int index);
    void on_gainComboBox_currentIndexChanged(int index);
    void on_irisComboBox_currentIndexChanged(int index);
    void on_shutterSpeedComboBox_currentIndexChanged(int index);
    void on_dnrComboBox_currentIndexChanged(int index);

    void changeShutterUI(QString);
    void changeIrisUI(QString);
    void changeGainUI(QString);
    void changeDNRUI(QString);

signals:
    void sig_dnnIndexChanged(int);
};

#endif // INDICATORCAMERAEXPOSEWIDGET_H
