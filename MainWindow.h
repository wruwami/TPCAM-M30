#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginWidget;
class DateTimeWidget;
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
    void on_dateTimeWidgetClicked();
    void on_dateTimeWidgetCanceled();
private:
    Ui::MainWindow *ui;
    LoginWidget* m_pLoginWidget = nullptr;
//    IndicatorWidget* m_pIndicatorWidget;
    MainMenuContentWidget* m_pMainMenuContentWidget = nullptr;
    DateTimeWidget* m_dateTimeWidget = nullptr;
};

#endif // MAINWINDOW_H
