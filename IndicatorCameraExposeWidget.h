#ifndef INDICATORCAMERAEXPOSEWIDGET_H
#define INDICATORCAMERAEXPOSEWIDGET_H

#include <QWidget>
#include <QDialog>

#include "SerialControlVisca.h"

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
    SerialControlVisca m_serialControlVisca;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_showHidePushButton_clicked();
    void on_speedPushButton_clicked();
    void on_hlcOnPushButton_clicked();
    void on_defogOffPushButton_clicked();
    void on_disOffPushButton_clicked();
    void on_dnrOnPushButton_clicked();
};

#endif // INDICATORCAMERAEXPOSEWIDGET_H
