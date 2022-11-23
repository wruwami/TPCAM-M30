#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include <QMap>

enum Dialog
{
    LoginExpiredDateWidgetType,
    IndicatorGPSWidgetType,
    Setting1LocationWidgetType,
    Setting3SystemInfoWidgetType,
    Setting3FactoryDefaultWidgetType,
    AdminPWWidgetType,
    PasswordChangingWidgetType,
    NEtworkPWWidgetType,
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
    explicit BaseDialog(Dialog, QWidget *parent = 0);
    ~BaseDialog();
private:
    Ui::BaseDialog *ui;
//    QMap<QString, QString>
};

#endif // BASEDIALOG_H
