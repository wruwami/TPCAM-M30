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
    void hide();
    void show();
    void setOutFrame(bool isSet);
private:
    bool m_bHide = false;
    bool m_isSetOutLine = false;
private slots:
    void on_hidePushButton_clicked();
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::EnforcementComponentWidget *ui;
};

#endif // ENFORCEMENTCOMPONENTWIDGET_H
