#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QDateTime>

class CustomPushButton;
namespace Ui {
class DateTimeWidget;
}

class DateTimeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();
private:
    void setDateTimeValue();
public:
    QWidget* m_pSavePushButton;
    QWidget* m_pCancelPushButton;
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
// void on_savePushButton_clicked();

// void on_cancelPushButton_clicked();

private:
    QDateTime m_dateTime;

private:
    Ui::DateTimeWidget *ui;
};

#endif // DATETIMEWIDGET_H
