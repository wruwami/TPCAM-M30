/**
 * @file SelfTestWarningMessageWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 셀프테스트 실패 표시 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SELFTESTWARNINGMESSAGEWIDGET_H
#define SELFTESTWARNINGMESSAGEWIDGET_H

#include <QWidget>
#include <QDialog>
#include "SelfTestWidget.h"

namespace Ui {
class SelfTestWarningMessageWidget;
}

class SelfTestWarningMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelfTestWarningMessageWidget(Status, Status, Status, Status,QDialog *parent = 0);
    ~SelfTestWarningMessageWidget();

private:
    QDialog* m_pParent;
private slots:
    void on_continuePushButton_clicked();

    void on_powerOffPushButton_clicked();

private:
    Ui::SelfTestWarningMessageWidget *ui;
};

#endif // SELFTESTWARNINGMESSAGEWIDGET_H
