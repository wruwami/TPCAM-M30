#ifndef CAMERAALIGNWIDGET_H
#define CAMERAALIGNWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class CameraAlignWidget;
}

class CameraAlignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraAlignWidget(QWidget *parent = 0);
    ~CameraAlignWidget();
public:
    CustomPushButton* m_pHomeButton;
private:
    Ui::CameraAlignWidget *ui;
};

#endif // CAMERAALIGNWIDGET_H
