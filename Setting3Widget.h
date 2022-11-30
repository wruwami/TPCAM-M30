#ifndef SETTING3WIDGET_H
#define SETTING3WIDGET_H

#include <QWidget>

namespace Ui {
class Setting3Widget;
}

class Setting3Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting3Widget(QWidget *parent = 0);
    ~Setting3Widget();

private slots:
    void on_showInfoPushButton_clicked();

    void on_factoryDefaultPushButton_clicked();

    void on_adminPWPushButton_clicked();

private:
    Ui::Setting3Widget *ui;
};

#endif // SETTING3WIDGET_H
