#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginWidget;
//class IndicatorWidget;
class MainMenuContentWidget;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cameraPushButton_clicked();

    void on_daynNightPushButton_clicked();
    void on_loginWidgetClose();
private:
    Ui::MainWindow *ui;
    LoginWidget* m_pLoginWidget;
//    IndicatorWidget* m_pIndicatorWidget;
    MainMenuContentWidget* m_pMainMenuContentWidget;
};

#endif // MAINWINDOW_H
