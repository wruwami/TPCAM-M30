#ifndef SETTING5WIDGET_H
#define SETTING5WIDGET_H

#include <QWidget>

namespace Ui {
class Setting5Widget;
}

class Setting5Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Setting5Widget(QWidget *parent = 0);
    ~Setting5Widget();
private:
    void setDHCPMode();
    void setManualMode();
private slots:
    void on_ipAddressComboBox_currentIndexChanged(int index);

private:
    Ui::Setting5Widget *ui;
};

#endif // SETTING5WIDGET_H
