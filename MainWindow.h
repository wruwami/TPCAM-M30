#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginWidget;
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

private:
    Ui::MainWindow *ui;
    LoginWidget* m_pLoginWidget;
};

#endif // MAINWINDOW_H
