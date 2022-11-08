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
};

#endif // SELFTESTWIDGET_H
