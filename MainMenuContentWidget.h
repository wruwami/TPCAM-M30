#ifndef MAINMENUCONTENTWIDGET_H
#define MAINMENUCONTENTWIDGET_H

#include <QWidget>

namespace Ui {
class MainMenuContentWidget;
}

class MainMenuContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuContentWidget(QWidget *parent = 0);
    ~MainMenuContentWidget();

private:
    Ui::MainMenuContentWidget *ui;
};

#endif // MAINMENUCONTENTWIDGET_H
