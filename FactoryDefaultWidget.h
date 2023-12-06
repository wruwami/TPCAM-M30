/**
 * @file FactoryDefaultWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 공장초기화 표시 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FACTORYDEFAULTWIDGET_H
#define FACTORYDEFAULTWIDGET_H

#include <QWidget>

namespace Ui {
class FactoryDefaultWidget;
}

class FactoryDefaultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FactoryDefaultWidget(QWidget *parent = 0);
    ~FactoryDefaultWidget();
     void MoveFactorySetting();
private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::FactoryDefaultWidget *ui;
    QDialog* m_pParent;
};

#endif // FACTORYDEFAULTWIDGET_H
