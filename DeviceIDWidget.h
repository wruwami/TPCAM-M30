#ifndef DEVICEIDWIDGET_H
#define DEVICEIDWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class DeviceIDWidget;
}

class DeviceIDWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceIDWidget(QWidget *parent = 0);
    ~DeviceIDWidget();
public:
    CustomPushButton* m_pSaveButton;
    CustomPushButton* m_pCancelButton;
private slots:
    void on_inputPushButton_clicked();

private:
    Ui::DeviceIDWidget *ui;
};

#endif // DEVICEIDWIDGET_H
