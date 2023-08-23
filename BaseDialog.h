#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include "SelfTestWidget.h"
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
    NetworkPasswordChangingWidgetType,
    NetworkPWWidgetType,
    WifiSearchWidgetType,
    BluetoothSearchFilterWidgetType,
    EnforcementWarningMessageWidgetType,
    FileManagerErrorMessageWidgetType,
    FileManagerQuestionMessageWidgetType,
    FileManagerFileTransferWidgetType,
    SearchBoxType,
    SdCardMemoryLackType,
};

namespace Ui {
class BaseDialog;
}

class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(Dialog, Qt::Alignment = Qt::AlignmentFlag::AlignLeft, QString = "", bool = false, QString title_text = "", QWidget *parent = 0);
    explicit BaseDialog(Dialog, Status, Status, Status, Status, Qt::Alignment = Qt::AlignmentFlag::AlignLeft, QWidget *parent = 0);
    explicit BaseDialog(Dialog, Qt::Alignment = Qt::AlignmentFlag::AlignLeft, QWidget* pWidget = nullptr, QWidget *parent = 0);
    virtual ~BaseDialog();
    void setAvFileFormatList(QList<AVFileFormat> avFileFormatList);
    void SetSelfTestResult(bool camera, bool laser, bool battery, bool storage);
    QWidget *pWidget() const;

private:
    void setSize(QSize size);
    void setSize(int w, int h);
    void drawBorder(QRect);
private:
    Ui::BaseDialog *ui;
    bool m_bIsCloseButton;
    bool m_isCamera;
    bool m_isLaser;
    bool m_isBattery;
    bool m_isStorage;
    QString m_strRet;
//    QWidget* m_pWidget = nullptr;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_closePushButton_clicked();
};

#endif // BASEDIALOG_H
