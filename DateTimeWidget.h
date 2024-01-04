/**
 * @file DateTimeWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief DateTime 설정하는 위젯
 * @details 설정방법은 수동 설정, GPS를 통한 설정 2가지가 있다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QJsonObject>


#include "ConfigManager.h"


class CustomLabel;
class CustomPushButton;
class CustomCheckBox;
namespace Ui {
class DateTimeWidget;
}

/**
 * @brief DateTime 설정하는 위젯 클래스
 * 
 */
class DateTimeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();
    void SetGPSUTCDateTime(QDateTime datetime);
private:
    void setDateTimeValue();
public:
    QWidget* m_pSavePushButton;
    QWidget* m_pCancelPushButton;
    QWidget* m_pParent;
    CustomCheckBox* m_pGPSCheckBox;
    CustomLabel* m_pYearLabel;// = new CustomLabel;
    CustomLabel* m_pMonthLabel;// = new CustomLabel;
    CustomLabel* m_pDayLabel;// = new CustomLabel;
    CustomPushButton* m_pYearPlusButton;// = new CustomPushButton;
    CustomPushButton* m_pYearMinusButton;// = new CustomPushButton;
    CustomPushButton* m_pMonthPlusButton;// = new CustomPushButton;
    CustomPushButton* m_pMonthMinusButton;// = new CustomPushButton;
    CustomPushButton* m_pDayPlusButton;// = new CustomPushButton;
    CustomPushButton* m_pDayMinusButton;// = new CustomPushButton;

private slots:
    void on_yearPlusPushButton_clicked();
    void on_yearMinusPushButton_clicked();
    void on_monthPlusPushButton_clicked();
    void on_monthMinusPushButton_clicked();
    void on_dayPlusPushButton_clicked();
    void on_dayMinusPushButton_clicked();
    void on_hourPlusPushButton_clicked();
    void on_hourMinusPushButton_clicked();
    void on_minutePlusPushButton_clicked();
    void on_minuteMinusPushButton_clicked();
    void on_secondPlusPushButton_clicked();
    void on_secondMinusPushButton_clicked();
    void on_savePushButton_clicked();
    void on_cancelPushButton_clicked();

    void on_timeZoneComboBox_currentIndexChanged(int index);    

private:
    QDateTime m_dateTime;
    QJsonObject m_jsonObject;
    QJsonObject m_newJsonObject;
    ConfigManager m_config = ConfigManager("setting_daytime.json");

private:
    Ui::DateTimeWidget *ui;
};

#endif // DATETIMEWIDGET_H
