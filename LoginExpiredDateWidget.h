#ifndef LOGINEXPIREDDATEWIDGET_H
#define LOGINEXPIREDDATEWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class LoginExpiredDateWidget;
}

class LoginExpiredDateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginExpiredDateWidget(QDialog *parent = 0);
    ~LoginExpiredDateWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginExpiredDateWidget *ui;
    QDialog* m_pParent;
};

#endif // LOGINEXPIREDDATEWIDGET_H
