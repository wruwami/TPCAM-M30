#ifndef ADMINPWWIDGET_H
#define ADMINPWWIDGET_H

#include <QWidget>

namespace Ui {
class AdminPWWidget;
}

class AdminPWWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPWWidget(QString msg = "", QWidget *parent = 0);
    ~AdminPWWidget();

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::AdminPWWidget *ui;
    QDialog* m_pParent;
//signals:
//    void sig_sendPW(QString);
};

#endif // ADMINPWWIDGET_H
