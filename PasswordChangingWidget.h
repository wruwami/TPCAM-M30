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
    Ui::PasswordChangingWidget *ui;
};

#endif // PASSWORDCHANGINGWIDGET_H
