#ifndef INDICATORCAMERAEXPOSEWIDGET_H
#define INDICATORCAMERAEXPOSEWIDGET_H

#include <QWidget>

namespace Ui {
class IndicatorCameraExposeWidget;
}

class IndicatorCameraExposeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorCameraExposeWidget(QWidget *parent = 0);
    ~IndicatorCameraExposeWidget();

private:
    Ui::IndicatorCameraExposeWidget *ui;
};

#endif // INDICATORCAMERAEXPOSEWIDGET_H
