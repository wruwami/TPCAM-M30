#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>

#include "FileFormat.h"

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
    SearchBoxType,
};

namespace Ui {
class BaseDialog;
}

class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(Dialog, Qt::Alignment = Qt::AlignmentFlag::AlignLeft, QString = "", bool = false, QString title_text = "", QWidget *parent = 0);
    ~BaseDialog();
    void setAvFileFormatList(QList<AVFileFormat> avFileFormatList);
    void SetSelfTestResult(bool camera, bool laser, bool battery, bool storage);
private:
    void setSize(QSize size);
    void setSize(int w, int h);
    void drawBorder(QRect);
private:
    Ui::BaseDialog *ui;
    bool m_bIsCloseButton;
    bool isCamera;
    bool isLaser;
    bool isBattery;
    bool isStorage;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_closePushButton_clicked();
};

#endif // BASEDIALOG_H
