#ifndef INDICATORCAMERAFOCUSWIDGET_H
#define INDICATORCAMERAFOCUSWIDGET_H

#include <QDialog>


enum FocusMode {
    Focus_Ready,
    Focus_AT,
    Focus_Manual,
};

class SerialLaserManager;
class SerialViscaManager;
class CustomPushButton;
namespace Ui {
class IndicatorCameraFocusWidget;
}

class IndicatorCameraFocusWidget : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorCameraFocusWidget(QWidget *parent = nullptr);
    ~IndicatorCameraFocusWidget();
private:
    void hide();
    void show();
public:
    CustomPushButton* m_pAutoTriggerPushButton;
private:
    Ui::IndicatorCameraFocusWidget *ui;
    bool m_bHide = false;
    FocusMode m_nMode = Focus_Ready;
    SerialViscaManager* m_pserialViscaManager;
    SerialLaserManager* m_pserialLaserManager;
    QString m_FocusValue;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_showHidePushButton_clicked();
    void on_speedPushButton_clicked();
    void on_onePushTriggerPushButton_clicked();
    void on_forcusDownPushButton_clicked();
    void on_forcusPlusPushButton_clicked();
    void on_show_focus(QString);
//    void on_applyPushButton_clicked();
    void on_autoTriggerPushButton_clicked(bool checked);
    void showDistanceSensitivity(float, int);
};

#endif // INDICATORCAMERAFOCUSWIDGET_H
