#ifndef INDICATORCAMERAEXPOSEWIDGET_H
#define INDICATORCAMERAEXPOSEWIDGET_H

#include <QWidget>
#include <Qdialog>

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


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // INDICATORCAMERAEXPOSEWIDGET_H
