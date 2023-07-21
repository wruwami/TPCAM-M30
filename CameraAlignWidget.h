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
    bool m_bHUDChecked = false;
    bool m_bCameraChecked = false;
private slots:
    void on_hudPushButton_clicked();

    void on_cameraPushButton_clicked();

private:
    Ui::CameraAlignWidget *ui;
};

#endif // CAMERAALIGNWIDGET_H
