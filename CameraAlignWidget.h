#ifndef CAMERAALIGNWIDGET_H
#define CAMERAALIGNWIDGET_H

#include <QWidget>

namespace Ui {
class CameraAlignWidget;
}

class CameraAlignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraAlignWidget(QWidget *parent = 0);
    ~CameraAlignWidget();

private:
    Ui::CameraAlignWidget *ui;
};

#endif // CAMERAALIGNWIDGET_H
