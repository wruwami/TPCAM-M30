/**
 * @file HomeButtonWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 메인메뉴 홈버튼 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef HOMEBUTTONWIDGET_H
#define HOMEBUTTONWIDGET_H

#include <QWidget>

class CustomPushButton;
namespace Ui {
class HomeButtonWidget;
}

/**
 * @brief 메인메뉴 홈버튼 위젯 클래스
 * 
 */
class HomeButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeButtonWidget(QWidget *parent = 0);
    ~HomeButtonWidget();
public:
    CustomPushButton* m_pHomePushButton;
private:
    Ui::HomeButtonWidget *ui;
};

#endif // HOMEBUTTONWIDGET_H
