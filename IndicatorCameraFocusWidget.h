#ifndef INDICATORCAMERAFOCUSWIDGET_H
#define INDICATORCAMERAFOCUSWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class IndicatorCameraFocusWidget;
}

class IndicatorCameraFocusWidget : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorCameraFocusWidget(QWidget *parent = nullptr);
    ~IndicatorCameraFocusWidget();

private:
    Ui::IndicatorCameraFocusWidget *ui;
    bool m_bHide = false;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_showHidePushButton_clicked();
};

#endif // INDICATORCAMERAFOCUSWIDGET_H
