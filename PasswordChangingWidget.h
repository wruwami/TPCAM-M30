/**
 * @file PasswordChangingWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 패스워드 변경 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PASSWORDCHANGINGWIDGET_H
#define PASSWORDCHANGINGWIDGET_H

#include <QWidget>

namespace Ui {
class PasswordChangingWidget;
}

class PasswordChangingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordChangingWidget(bool, QWidget *parent = 0);
    ~PasswordChangingWidget();
private:
    QDialog* m_pParent;
private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::PasswordChangingWidget *ui;
    bool m_bNetwork;
signals:
    void sig_sendPW(QString);
};

#endif // PASSWORDCHANGINGWIDGET_H
