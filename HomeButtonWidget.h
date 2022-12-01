#ifndef HOMEBUTTONWIDGET_H
#define HOMEBUTTONWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class HomeButtonWidget;
}

class HomeButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeButtonWidget(QWidget *parent = 0);
    ~HomeButtonWidget();
public:
    CustomPushButton* m_pHomePushButton;
private:
    Ui::HomeButtonWidget *ui;
};

#endif // HOMEBUTTONWIDGET_H
