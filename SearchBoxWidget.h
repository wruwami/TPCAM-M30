#ifndef SEARCHBOXWIDGET_H
#define SEARCHBOXWIDGET_H

#include <QWidget>

namespace Ui {
class SearchBoxWidget;
}

class SearchBoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBoxWidget(QWidget *parent = 0);
    ~SearchBoxWidget();

private slots:
    void on_firstPlusButton_clicked();

    void on_firstMinusButton_clicked();

    void on_secondPlusButton_clicked();

    void on_secondMinusButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

private:
    Ui::SearchBoxWidget *ui;
    int firstValue = 0;
    int secondValue = 60;
};

#endif // SEARCHBOXWIDGET_H
