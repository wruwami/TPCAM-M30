#ifndef SETTING4STAWIDGET_H
#define SETTING4STAWIDGET_H

#include <QWidget>

namespace Ui {
class Setting4STAWidget;
}

class Setting4STAWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting4STAWidget(QWidget *parent = 0);
    ~Setting4STAWidget();

private:
    Ui::Setting4STAWidget *ui;
};

#endif // SETTING4STAWIDGET_H
