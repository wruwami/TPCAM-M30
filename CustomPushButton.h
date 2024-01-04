/**
 * @file CustomPushButton.h
 * @author wruwami (wruwami@naver.com)
 * @brief QPushButton 상속하여 공통으로 사용하는 PushButton 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QToolButton>

/**
 * @brief QPushButton 상속하여 공통으로 사용하는 PushButton 위젯 클래스
 * 
 */
class CustomPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomPushButton(QWidget *parent = 0);
    void setImage(QString path_name, QString file_name);
    void setImage(QString path_name, QString file_name, QSize size);
    void setFontSize(int);
signals:

private:
    QPixmap m_pixmap;
    QSize m_size;
    QIcon m_icon;
    float m_ratio = 0;
//    QSize max;
//    QSize min;
//    bool settingText = false;
public slots:

//public:
// void setT5ext(const QString text);
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // CUSTOMPUSHBUTTON_H
