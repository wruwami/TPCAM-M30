/**
 * @file Color.h
 * @author wruwami (wruwami@naver.com)
 * @brief 위젯 백그라운드 컬러 설정 기능
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef COLOR_H
#define COLOR_H

#include <QPalette>
#include <QWidget>
#include <QPushButton>
#include <QColor>

enum Color
{
};

static void setBackGroundColor(QWidget* widget, QColor color)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
    widget->update();
}

static void setBackGroundColor(QWidget* widget, Color color)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
    widget->update();
}

static void setBackGroundColor(QWidget* widget, int hex)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, hex);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
    widget->update();
}

static void setBackGroundColor(QPushButton* widget, int hex)
{
    QColor col = QColor(hex);
    if (col.isValid())
    {
        QPalette pal = widget->palette();
//        QPalette pal = QPalette();
        pal.setColor(QPalette::Button, QColor(Qt::blue));
        widget->setAutoFillBackground(true);
//        widget->setBackgroundRole(QPalette::ColorRole::Button);
        widget->setPalette(pal);
//        widget->show();

    }
}

//static void setTextColor(QWidget* widget, QColor color)
//{
//    QPalette pal = QPalette();
//    pal.setColor(widget->foregroundRole(), color);
//    widget->setAutoFillBackground(true);
//    widget->setPalette(pal);
//    widget->update();
//}

//static void setTextColor(QWidget* widget, int color)
//{
//    QPalette pal = QPalette();
//    pal.setColor(widget->foregroundRole(), color);
//    widget->setAutoFillBackground(true);
//    widget->setPalette(pal);
//    widget->update();
//}


#endif // COLOR_H
