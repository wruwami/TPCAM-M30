#ifndef SELFTESTWIDGET_H
#define SELFTESTWIDGET_H

#include <QDialog>

namespace Ui {
class SelfTestWidget;
}

class SelfTestWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SelfTestWidget(QWidget *parent = 0);
    ~SelfTestWidget();

private:
    Ui::SelfTestWidget *ui;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SELFTESTWIDGET_H
