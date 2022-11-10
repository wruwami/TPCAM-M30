#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>

namespace Ui {
class MainMenuWidget;
}

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = 0);
    ~MainMenuWidget();
    void SetMainMenuTitle(QString title);
private:
    Ui::MainMenuWidget *ui;



    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINMENUWIDGET_H
