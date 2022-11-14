#ifndef INDICATORCAMERAWIDGET_H
#define INDICATORCAMERAWIDGET_H

#include <QWidget>

namespace Ui {
class IndicatorCameraWidget;
}

class IndicatorCameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorCameraWidget(QWidget *parent = nullptr);
    ~IndicatorCameraWidget();

private:
    Ui::IndicatorCameraWidget *ui;
};

#endif // INDICATORCAMERAWIDGET_H
