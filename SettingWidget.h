#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class Setting1Widget;
class Setting2Widget;
class Setting3Widget;
class Setting4APWidget;
class Setting5Widget;
class Setting6Widget;
class Setting7Widget;
class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();
private:
    void clearStyleSheet();
public:
    QWidget* m_pSavePushButton;
    QWidget* m_pCancelPushButton;
private:
    Setting1Widget* m_pSetting1Widget;
    Setting2Widget* m_pSetting2Widget;
    Setting3Widget* m_pSetting3Widget;
    Setting4APWidget* m_pSetting4APWidget;
    Setting5Widget* m_pSetting5Widget;
    Setting6Widget* m_pSetting6Widget;
    Setting7Widget* m_pSetting7Widget;

private slots:
    void on_setting1PushButton_clicked();
    void on_setting2PushButton_clicked();
    void on_setting3PushButton_clicked();
    void on_setting4PushButton_clicked();
    void on_setting5PushButton_clicked();
    void on_setting6PushButton_clicked();
    void on_setting7PushButton_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_savePushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
