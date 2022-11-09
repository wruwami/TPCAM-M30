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

private:
    Ui::MainMenuAdminAlignWidget *ui;
};

#endif // MAINMENUADMINALIGNWIDGET_H
