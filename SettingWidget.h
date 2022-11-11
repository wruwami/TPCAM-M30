#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QDialog>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

private slots:
    void on_setting1PushButton_clicked();

    void on_setting2PushButton_clicked();

    void on_setting3PushButton_clicked();

    void on_setting4PushButton_clicked();

    void on_setting5PushButton_clicked();

    void on_setting6PushButton_clicked();

    void on_setting7PushButton_clicked();

    void on_savePushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
