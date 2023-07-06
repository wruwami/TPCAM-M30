#ifndef CAMERAZOOMFOCUSWIDGET_H
#define CAMERAZOOMFOCUSWIDGET_H

#include <QWidget>
#include "SerialViscaManager.h"

namespace Ui {
class CameraZoomFocusWidget;
}

class CameraZoomFocusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraZoomFocusWidget(QWidget *parent = 0);
    ~CameraZoomFocusWidget();

private slots:
    void on_optPushButton_clicked();

    void on_focusPlusPushButton_clicked();

    void on_FocusMinusPushButton_clicked();

private:
    Ui::CameraZoomFocusWidget *ui;
    SerialViscaManager m_serialViscaManager;
};

#endif // CAMERAZOOMFOCUSWIDGET_H
