#ifndef ENFORCEMENTSPEEDREADY_H
#define ENFORCEMENTSPEEDREADY_H

#include <QWidget>

namespace Ui {
class EnforcementSpeedReady;
}

class EnforcementSpeedReady : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementSpeedReady(QWidget *parent = 0);
    ~EnforcementSpeedReady();

private:
    Ui::EnforcementSpeedReady *ui;
};

#endif // ENFORCEMENTSPEEDREADY_H
