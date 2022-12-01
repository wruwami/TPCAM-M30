#ifndef HOMETITLEWIDGET_H
#define HOMETITLEWIDGET_H

#include <QWidget>

namespace Ui {
class HomeTitleWidget;
}

class HomeTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeTitleWidget(QWidget *parent = 0);
    ~HomeTitleWidget();

private:
    Ui::HomeTitleWidget *ui;
};

#endif // HOMETITLEWIDGET_H
