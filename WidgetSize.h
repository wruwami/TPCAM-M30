#ifndef WIDGETSIZE_H
#define WIDGETSIZE_H

#include <QRect>
#include <QScreen>
#include <QSize>
#include <QPoint>

enum Size
{
    PatientInfoWidgetWidth = 430,
    PatientInfoWidgetHeight = 95,
    AlarmMessageWidth = 840,
    AlarmMessageHeight = 95,
    AlarmPauseTimeWidth = 205,
    AlarmPauseTimeHeight = 95,
    DateTimeWidth = 225,
    DateTimeHeight = 95,
    IconWidth = 220,
    IconHeight = 95,
    WaveformWidth = 1035,
    WaveformHeight = 615,
    FirstParameterValueHeight1 = 205,
    FirstParameterValueHeight2 = 185,
    ParameterValueWidth = 1035,
    ParameterValueHeight = 185,
    OperationModeWidth = 1035,
    OperationModeHeight = 185,
    MenuWidth = 220,
    MenuHeight,
    FirstParameterWidth = 665,
    ShortCutWidth = 220,
    ShortCutHeight = 95,
};

class WidgetSize
{
private:
    WidgetSize();
    WidgetSize(const WidgetSize& other);
    ~WidgetSize() {};
    static WidgetSize* instance;
public:
    static WidgetSize* GetInstance()
    {
        if(instance == nullptr) instance = new WidgetSize();
        return instance;
    }
    void initilize(QScreen* screen);
    int getScreenWidth();
    int getScreenHeight();
    QRect GetLeftWidgetRect();
    QRect GetSecondTabWidgetRect();
    QRect GetWidgetSizePos(QRect rect);
    QRect GetWidgetSizePos(QRect rect, QPoint oripos);
    QSize GetWidgetSize(QSize size);
    QPoint GetWidgetPos(QPoint pos);
    QPoint GetWidgetPos(QPoint pos, QPoint oripos);
    int GetFontSize(int fontsize);
    int GetWidgetHeight(int height);
    int GetWidgetWidth(int width);
private:
    QRect m_rec;
};

static QSize GetWidgetSize(QSize size)
{
    return WidgetSize::GetInstance()->GetWidgetSize(size);
}

static QRect GetWidgetSizePos(QRect rect)
{
    return WidgetSize::GetInstance()->GetWidgetSizePos(rect);
}

static QRect GetWidgetSizePos(QRect rect, QPoint point)
{
    return WidgetSize::GetInstance()->GetWidgetSizePos(rect, point);
}

static int GetFontSize(int fontsize)
{
    return WidgetSize::GetInstance()->GetFontSize(fontsize);
}

static int getScreenWidth()
{
    return WidgetSize::GetInstance()->getScreenWidth();
}

static int getScreenHeight()
{
    return WidgetSize::GetInstance()->getScreenHeight();
}

static int GetWidthHeight(int height)
{
    return WidgetSize::GetInstance()->GetWidgetHeight(height);
}

static int GetWidthWidth(int width)
{
    return WidgetSize::GetInstance()->GetWidgetWidth(width);
}
#endif // WIDGETSIZE_H
