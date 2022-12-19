#ifndef ENFORCEMENTCOMPONENTWIDGET_H
#define ENFORCEMENTCOMPONENTWIDGET_H

#include <QWidget>

namespace Ui {
class EnforcementComponentWidget;
}

class EnforcementComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementComponentWidget(QWidget *parent = 0);
    ~EnforcementComponentWidget();
private:
    bool m_bHide = false;
private slots:
    void on_hidePushButton_clicked();

private:
    Ui::EnforcementComponentWidget *ui;
};

#endif // ENFORCEMENTCOMPONENTWIDGET_H
