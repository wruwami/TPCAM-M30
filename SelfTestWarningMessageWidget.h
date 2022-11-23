#ifndef SELFTESTWARNINGMESSAGEWIDGET_H
#define SELFTESTWARNINGMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class SelfTestWarningMessageWidget;
}

class SelfTestWarningMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelfTestWarningMessageWidget(QWidget *parent = 0);
    ~SelfTestWarningMessageWidget();

private:
    Ui::SelfTestWarningMessageWidget *ui;
};

#endif // SELFTESTWARNINGMESSAGEWIDGET_H
