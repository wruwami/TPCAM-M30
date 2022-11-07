#ifndef ENFORCEMENTCAMERA_H
#define ENFORCEMENTCAMERA_H

#include <QWidget>

namespace Ui {
class EnforcementCamera;
}

class EnforcementCamera : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementCamera(QWidget *parent = 0);
    ~EnforcementCamera();

private:
    Ui::EnforcementCamera *ui;
};

#endif // ENFORCEMENTCAMERA_H
