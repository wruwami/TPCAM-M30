/**
 * @file LoginExpiredDateWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief expired_date에 따라 동작하는 경고 메세지 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LOGINEXPIREDDATEWIDGET_H
#define LOGINEXPIREDDATEWIDGET_H

#include <QWidget>
#include <QDialog>

#include "SoundPlayer.h"

namespace Ui {
class LoginExpiredDateWidget;
}

/**
 * @brief expired_date에 따라 동작하는 경고 메세지 위젯 클래스
 * 
 */
class LoginExpiredDateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginExpiredDateWidget(QDialog *parent = 0);
    ~LoginExpiredDateWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginExpiredDateWidget *ui;
    QDialog* m_pParent;
};

#endif // LOGINEXPIREDDATEWIDGET_H
