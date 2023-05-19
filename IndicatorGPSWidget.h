#ifndef INDICATORGPSWIDGET_H
#define INDICATORGPSWIDGET_H

#include <QWidget>

namespace Ui {
class IndicatorGPSWidget;
}

class IndicatorGPSWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorGPSWidget(QWidget *parent = 0);
    ~IndicatorGPSWidget();
private:
    Ui::IndicatorGPSWidget *ui;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // INDICATORGPSWIDGET_H
