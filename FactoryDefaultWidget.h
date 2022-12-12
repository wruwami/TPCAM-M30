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

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::FactoryDefaultWidget *ui;
    QDialog* m_pParent;
};

#endif // FACTORYDEFAULTWIDGET_H
