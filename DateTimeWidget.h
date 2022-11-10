#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QDialog>
#include <QDateTime>

class CustomPushButton;
namespace Ui {
class DateTimeWidget;
}

class DateTimeWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

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
public:
    CustomPushButton* m_cancelButton;

private:
    QDateTime m_dateTime;

private:
    Ui::DateTimeWidget *ui;
};

#endif // DATETIMEWIDGET_H
