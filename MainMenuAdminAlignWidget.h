#ifndef MAINMENUADMINALIGNWIDGET_H
#define MAINMENUADMINALIGNWIDGET_H

#include <QWidget>

namespace Ui {
class MainMenuAdminAlignWidget;
}

class MainMenuAdminAlignWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuAdminAlignWidget(QWidget *parent = 0);
    ~MainMenuAdminAlignWidget();
public:
    QWidget* m_pDeviceIdWidget;
    QWidget* m_pCameraAlignWidget;
    QWidget* m_pCameraZoomFocusWidget;
private slots:
//    void on_deviceIDPushButton_clicked();

//    void on_cameraHUDAlignPushButton_clicked();

//    void on_cameraZoomFocusPushButton_clicked();

private:
    Ui::MainMenuAdminAlignWidget *ui;
};

#endif // MAINMENUADMINALIGNWIDGET_H
