#ifndef INDICATORCAMERAWIDGET_H
#define INDICATORCAMERAWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class IndicatorWidget;
}

class IndicatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorWidget(QWidget *parent = 0);
    ~IndicatorWidget();
private:
    void clearSecondRow();
private slots:
    void on_cameraPushButton_clicked();

    void on_screenRecordingPushButton_clicked();

    void on_daynNightPushButton_clicked();

    void on_gpsPushButton_clicked();

    void on_comPushButton_clicked();

    void on_speedPushButton_clicked();

    void on_enforcementPushButton_clicked();

    void on_weatherPushButton_clicked();

private:
    Ui::IndicatorWidget *ui;
    CustomPushButton* m_pSunnyPushButton;
    CustomPushButton* m_pRainyPushButton;
    CustomPushButton* m_pImagePushButton;
    CustomPushButton* m_pImageVideoPushButton;
    CustomPushButton* m_pVideoPushButton;
    CustomPushButton* m_pSTPushButton;
    CustomPushButton* m_pLTPushButton;
    CustomPushButton* m_pWifiPushButton;
    CustomPushButton* m_pBTPushButton;
    CustomPushButton* m_pEthernetPushButton;
};

#endif // INDICATORCAMERAWIDGET_H
