#ifndef MAINMENUCONTENTWIDGET_H
#define MAINMENUCONTENTWIDGET_H

#include <QWidget>

class QPushButton;
class CustomImageWidget;
namespace Ui {
class MainMenuContentWidget;
}

class MainMenuContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuContentWidget(QWidget *parent = 0);
    ~MainMenuContentWidget();

private slots:
    void on_settingPushButton_clicked();

    void on_fileManagementPushButton_clicked();
    void on_enforcementPushButton_clicked();

public:
    CustomImageWidget* m_pEnforcementButton;
private:
    Ui::MainMenuContentWidget *ui;

};

#endif // MAINMENUCONTENTWIDGET_H
