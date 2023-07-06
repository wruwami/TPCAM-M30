#ifndef INDICATORCAMERAFOCUSWIDGET_H
#define INDICATORCAMERAFOCUSWIDGET_H

#include <QDialog>

#include "SerialViscaManager.h"

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
private:
    Ui::IndicatorCameraFocusWidget *ui;
    bool m_bHide = false;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_showHidePushButton_clicked();
    void on_speedPushButton_clicked();
    void on_autoTriggerPushButton_clicked();
    void on_onePushTriggerPushButton_clicked();
    void on_forcusDownPushButton_clicked();
    void on_forcusPlusPushButton_clicked();
//    void on_applyPushButton_clicked();
};

#endif // INDICATORCAMERAFOCUSWIDGET_H
