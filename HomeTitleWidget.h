/**
 * @file HomeTitleWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 메인메뉴 타이틀 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef HOMETITLEWIDGET_H
#define HOMETITLEWIDGET_H

#include <QWidget>

namespace Ui {
class HomeTitleWidget;
}

/**
 * @brief 메인메뉴 타이틀 위젯 클래스
 * 
 */
class HomeTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeTitleWidget(QWidget *parent = 0);
    ~HomeTitleWidget();

private:
    Ui::HomeTitleWidget *ui;
};

#endif // HOMETITLEWIDGET_H
