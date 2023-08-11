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

private:
    Ui::IndicatorCameraExposeWidget *ui;
    bool m_bHide = false;
    SerialViscaManager* m_serialViscaManager = nullptr;
    bool m_bDNR = false;
    bool m_bDIS = false;
    bool m_bDEFOG = false;
    bool m_bHLC = false;

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
};

#endif // INDICATORCAMERAEXPOSEWIDGET_H
