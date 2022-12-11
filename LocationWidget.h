#ifndef LOCATIONWIDGET_H
#define LOCATIONWIDGET_H

#include <QWidget>

namespace Ui {
class LocationWidget;
}

class LocationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LocationWidget(QWidget *parent = 0);
    ~LocationWidget();

private:
    Ui::LocationWidget *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // LOCATIONWIDGET_H
