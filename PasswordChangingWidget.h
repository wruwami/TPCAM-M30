#ifndef PASSWORDCHANGINGWIDGET_H
#define PASSWORDCHANGINGWIDGET_H

#include <QWidget>

namespace Ui {
class PasswordChangingWidget;
}

class PasswordChangingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordChangingWidget(QWidget *parent = 0);
    ~PasswordChangingWidget();
private:
    QDialog* m_pParent;
private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::PasswordChangingWidget *ui;
};

#endif // PASSWORDCHANGINGWIDGET_H
