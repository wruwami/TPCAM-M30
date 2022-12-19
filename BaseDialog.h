#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include <QMap>

enum Dialog
{
    SelfTestWarningMessageWidgetType,
    LoginExpiredDateWidgetType,
    IndicatorGPSWidgetType,
    Setting1LocationWidgetType,
    Setting3SystemInfoWidgetType,
    Setting3FactoryDefaultWidgetType,
    AdminPWWidgetType,
    PasswordChangingWidgetType,
    NetworkPWWidgetType,
    WifiSearchWidgetType,
    BluetoothSearchFilterWidgetType,
    EnforcementWarningMessageWidgetType,
    FileManagerErrorMessageWidgetType,
    FileManagerQuestionMessageWidgetType,
    FileManagerFileTransferWidgetType,
};

namespace Ui {
class BaseDialog;
}

class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(Dialog, Qt::Alignment = Qt::AlignmentFlag::AlignLeft, QString = "", bool = false, QWidget *parent = 0);
    ~BaseDialog();
private:
    void setSize(QSize size);
    void setSize(int w, int h);
private:
    Ui::BaseDialog *ui;
    bool m_bIsCloseButton;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_closePushButton_clicked();
};

#endif // BASEDIALOG_H
