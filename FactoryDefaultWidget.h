#ifndef FACTORYDEFAULTWIDGET_H
#define FACTORYDEFAULTWIDGET_H

#include <QWidget>

namespace Ui {
class FactoryDefaultWidget;
}

class FactoryDefaultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FactoryDefaultWidget(QWidget *parent = 0);
    ~FactoryDefaultWidget();

private:
    Ui::FactoryDefaultWidget *ui;
};

#endif // FACTORYDEFAULTWIDGET_H
