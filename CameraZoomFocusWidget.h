#ifndef CAMERAZOOMFOCUSWIDGET_H
#define CAMERAZOOMFOCUSWIDGET_H

#include <QWidget>

namespace Ui {
class CameraZoomFocusWidget;
}

class CameraZoomFocusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraZoomFocusWidget(QWidget *parent = 0);
    ~CameraZoomFocusWidget();

private:
    Ui::CameraZoomFocusWidget *ui;
};

#endif // CAMERAZOOMFOCUSWIDGET_H
