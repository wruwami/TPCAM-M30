#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include <QWidget>

namespace Ui {
class SystemInfoWidget;
}

class SystemInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemInfoWidget(QWidget *parent = 0);
    ~SystemInfoWidget();

private:
    Ui::SystemInfoWidget *ui;
};

#endif // SYSTEMINFOWIDGET_H
