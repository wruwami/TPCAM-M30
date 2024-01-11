/**
 * @file AdminPWWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief Admin 비밀번호 확인 위젯  BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ADMINPWWIDGET_H
#define ADMINPWWIDGET_H

#include <QWidget>

namespace Ui {
class AdminPWWidget;
}

/**
 * @brief Admin 비밀번호 확인 위젯 클래스
 * 
 */
class AdminPWWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPWWidget(QString msg = "", QWidget *parent = 0);
    ~AdminPWWidget();

private slots:
/**
 * @brief 
 * 
 */
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::AdminPWWidget *ui;
    QDialog* m_pParent;
//signals:
//    void sig_sendPW(QString);
};

#endif // ADMINPWWIDGET_H
