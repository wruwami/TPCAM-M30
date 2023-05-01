#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QJsonObject>


#include "ConfigManager.h"

class CustomPushButton;
class CustomCheckBox;
namespace Ui {
class DateTimeWidget;
}

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
