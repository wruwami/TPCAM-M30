#include "WidgetSize.h"

#include <QApplication>

enum DefaultSize
{
    Width = 1600,
    Height = 960,
};

WidgetSize* WidgetSize::instance = nullptr;

//void WidgetSize::initilize(QScreen* screen)
//{
//#if QT_VERSION >= 6
//    m_rec = screen->geometry();
//#else
//    m_rec = screen->geometry();
//#endif
//}

WidgetSize::WidgetSize()
{
    m_rec = QApplication::primaryScreen()->geometry();
}

int WidgetSize::getScreenWidth()
{
    return m_rec.width();
}

int WidgetSize::getScreenHeight()
{
    return m_rec.height();
}

QRect WidgetSize::GetLeftWidgetRect()
{
    return QRect(0, m_rec.height() / 5, m_rec.width() / 3, m_rec.height() / 5 * 3);
}

QRect WidgetSize::GetSecondTabWidgetRect()
{
    return QRect(0, m_rec.height() / 5, m_rec.width() / 3 - 30, m_rec.height() / 5 * 3);
}

QRect WidgetSize::GetWidgetSizePos(QRect rect)
{
    // Width height
    QRect rect2 = QRect(rect.x() * m_rec.width() / Width , rect.y() * m_rec.height() / Height , rect.width() * m_rec.width() / Width , rect.height() * m_rec.height()/ Height );
    return rect2;
}

QRect WidgetSize::GetWidgetSizePos(QRect rect, QPoint oripos)
{
    int x = oripos.x() * Width / m_rec.width();
    int y = oripos.y() * Height / m_rec.height();
//    QRect orirect2 = QRect((orirect.x()) * Width  / m_rec.width() , (orirect.y()) * Height / m_rec.height() , orirect.width() * Width / m_rec.width(), orirect.height() * Height / m_rec.height() );
//    QRect rect2 = QRect((rect.x() - x)  * m_rec.width() / Width , (rect.y() -  y) * m_rec.height() / Height , rect.width() * m_rec.width() / Width , rect.height() * m_rec.height()/ Height );
    QRect rect2 = QRect((rect.x() - x)  * m_rec.width() / Width , ((rect.y() - y)) * m_rec.height() / Height , rect.width() * m_rec.width() / Width , rect.height() * m_rec.height()/ Height );
    return rect2;
}


QSize WidgetSize::GetWidgetSize(QSize size)
{
    // Width height
    return QSize(size.width() * m_rec.width() / Width , size.height() * m_rec.height()/ Height );
}

int WidgetSize::GetWidgetHeight(int height)
{
    return height * m_rec.height()/ Height;
}

int WidgetSize::GetWidgetWidth(int width)
{
    return width * m_rec.width()/ Width;
}

QRect WidgetSize::GetMainWindowRect()
{
    return m_mainWindowRect;
}

void WidgetSize::SetMainWindowRect(QRect rect)
{
    m_mainWindowRect = rect;
}

QPoint WidgetSize::GetWidgetPos(QPoint pos)
{
    return QPoint(pos.x() * m_rec.width() / Width , pos.y() * m_rec.height()/ Height );
}

QPoint WidgetSize::GetWidgetPos(QPoint pos, QPoint oripos)
{
//    return QPoint((pos.x() - oripos.x()) * m_rec.width() / Width , (pos.y() - oripos.y()) * m_rec.height()/ Height );

    int x = oripos.x() * Width / m_rec.width();
    int y = oripos.y() * Height / m_rec.height();
    return QPoint((pos.x() - x) * m_rec.width() / Width , (pos.y() - y) * m_rec.height()/ Height );
}

int WidgetSize::GetFontSize(int fontsize)
{
    int x = fontsize * m_rec.width() / Width * 2;
    int y = fontsize * m_rec.height() / Height * 2;
    return x;
}

int WidgetSize::CalcGap(int gap)
{
    int calc_gap = gap * Width / m_rec.width();
    return calc_gap;
}
