#ifndef INDICATORCAMERAFOCUSWIDGET_H
#define INDICATORCAMERAFOCUSWIDGET_H

#include <QWidget>

namespace Ui {
class IndicatorCameraFocusWidget;
}

class IndicatorCameraFocusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorCameraFocusWidget(QWidget *parent = nullptr);
    ~IndicatorCameraFocusWidget();

private:
    Ui::IndicatorCameraFocusWidget *ui;
};

#endif // INDICATORCAMERAFOCUSWIDGET_H
