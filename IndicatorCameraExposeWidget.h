#ifndef INDICATORCAMERAEXPOSEWIDGET_H
#define INDICATORCAMERAEXPOSEWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class IndicatorCameraExposeWidget;
}

class IndicatorCameraExposeWidget : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorCameraExposeWidget(QWidget *parent = 0);
    ~IndicatorCameraExposeWidget();

private:
    Ui::IndicatorCameraExposeWidget *ui;
    bool m_bHide = false;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_showHidePushButton_clicked();
};

#endif // INDICATORCAMERAEXPOSEWIDGET_H
