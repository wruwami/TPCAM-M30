#ifndef SELFTESTDIALOG_H
#define SELFTESTDIALOG_H

#include <QDialog>

namespace Ui {
class SelfTestDialog;
}

class SelfTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelfTestDialog(QWidget *parent = 0);
    ~SelfTestDialog();

private:
    QString GetVersion();
    void StartSelfTest();
    bool CameraTest();
    bool LaserTest();
    bool BatteryTest();
    bool StorageTest();
private:
    Ui::SelfTestDialog *ui;
    int m_nSecond = 0;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SELFTESTDIALOG_H
