#ifndef DEVICEIDWIDGET_H
#define DEVICEIDWIDGET_H

#include <QWidget>

namespace Ui {
class DeviceIDWidget;
}

class DeviceIDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceIDWidget(QWidget *parent = 0);
    ~DeviceIDWidget();

private:
    Ui::DeviceIDWidget *ui;
};

#endif // DEVICEIDWIDGET_H
