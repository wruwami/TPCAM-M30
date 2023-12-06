/**
 * @file MainMenuAdminAlignWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief admin-align유저로 로그인하면 나오는 화면 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
    QWidget* m_pLogoButton;
private slots:
//    void on_deviceIDPushButton_clicked();

//    void on_cameraHUDAlignPushButton_clicked();

//    void on_cameraZoomFocusPushButton_clicked();

private:
    Ui::MainMenuAdminAlignWidget *ui;
};

#endif // MAINMENUADMINALIGNWIDGET_H
