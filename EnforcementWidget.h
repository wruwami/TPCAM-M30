/**
 * @file EnforcementWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief Mainwindow와 EnforcementComponentWidget을 잇는 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENFORCEMENTWIDGET_H
#define ENFORCEMENTWIDGET_H

#include <QWidget>
#include "EnforcementComponentWidget.h"

namespace Ui {
class EnforcementWidget;
}

/**
 * @brief Mainwindow와 EnforcementComponentWidget을 잇는 위젯 클래스
 * 
 */
class EnforcementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementWidget(QWidget *parent = 0);
    ~EnforcementWidget();
    EnforcementComponentWidget* m_pEnforcementComponentWidget = nullptr;
private:
    Ui::EnforcementWidget *ui;
};

#endif // ENFORCEMENTWIDGET_H
