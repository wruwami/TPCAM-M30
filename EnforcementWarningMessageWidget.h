/**
 * @file EnforcementWarningMessageWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief SD카드 용량 에러 표시 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENFORCEMENTWARNINGMESSAGEWIDGET_H
#define ENFORCEMENTWARNINGMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class EnforcementWarningMessageWidget;
}

/**
 * @brief SD카드 용량 에러 표시 위젯 클래스
 * 
 */
class EnforcementWarningMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementWarningMessageWidget(QWidget *parent = 0);
    ~EnforcementWarningMessageWidget();

private:
    Ui::EnforcementWarningMessageWidget *ui;
};

#endif // ENFORCEMENTWARNINGMESSAGEWIDGET_H
