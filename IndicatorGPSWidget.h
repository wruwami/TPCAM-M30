/**
 * @file IndicatorGPSWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 인디케이터에서 GPS 정보를 보여주는 위젯, BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INDICATORGPSWIDGET_H
#define INDICATORGPSWIDGET_H

#include <QWidget>

namespace Ui {
class IndicatorGPSWidget;
}

/**
 * @brief 인디케이터에서 GPS 정보를 보여주는 위젯 클래스
 * 
 */
class IndicatorGPSWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorGPSWidget(QWidget *parent = 0);
    ~IndicatorGPSWidget();
private:
    Ui::IndicatorGPSWidget *ui;
    QByteArray m_tz;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // INDICATORGPSWIDGET_H
