#ifndef SETTING6WIDGET_H
#define SETTING6WIDGET_H

#include <QWidget>

namespace Ui {
class Setting6Widget;
}

class Setting6Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting6Widget(QWidget *parent = 0);
    ~Setting6Widget();

private slots:
    void on_searchPushButton_clicked();

private:
    Ui::Setting6Widget *ui;
};

#endif // SETTING6WIDGET_H
