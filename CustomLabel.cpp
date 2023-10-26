#include "CustomLabel.h"

#include "qdir.h"
#include <QFont>
#include <QDebug>

#define DEFAULT_PATH    "images"

#include "FontSize.h"
#include "WidgetSize.h"
#include "FileManager.h"

CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//void CustomLabel::setIconImage(QString path_name, QString file_name)
//{
//    QDir qdir;
//    QString file_full_path;
//    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;

//    QPixmap pixmap;
//    pixmap.load(file_full_path);
////    QPixmap fitpixmap=pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    this->seti
////    this->setScaledContents(true);
//}
void CustomLabel::setImageFromAvi(QString file_path, QSize size)
{
    m_pixmap.load(file_path);
    m_fitpixmap = m_pixmap.scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_fitpixmap);
//    this->setScaledContents(true);
}

void CustomLabel::setImage(QString file_path, QSize size)
{
    m_pixmap.load(file_path);
    m_fitpixmap = m_pixmap.scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_fitpixmap);
//    this->setScaledContents(true);
}

void CustomLabel::setImage(QString path_name, QString file_name)
{
    QDir qdir;
    QString file_full_path;
    file_full_path = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;


    m_pixmap.load(file_full_path);
    m_fitpixmap = m_pixmap;
//    QPixmap fitpixmap=pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_pixmap);
//    this->setScaledContents(true);
}

void CustomLabel::setImage(QString path_name, QString file_name, QSize size)
{
    QDir qdir;
    QString file_full_path;
    file_full_path = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;

    m_fitpixmap = m_pixmap;
    m_pixmap.load(file_full_path);
//    QPixmap fitpixmap=pixmap.scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_pixmap);
    //    this->setScaledContents(true);
}

//QPixmap CustomLabel::scaleImage(double factor)
//{
//    QPixmap m_fitpixmap;
//    m_fitpixmap = m_pixmap.scaled(factor * size());
//    return m_fitpixmap;
//}

void CustomLabel::setZoom(double factor, QRect rect)
{

    int x = (geometry().left() + geometry().right()) / factor;
    int y = (geometry().top() + geometry().bottom()) / factor;
//    x *= factor / 2;
//    y *= factor / 2;
//    int x = m_fitpixmap.width() / 2;
//    int y = m_fitpixmap.
    int width = geometry().width();
    int height = geometry().height();
//    x -= width / 2;
//    y -= height / 2;
    QPixmap pixmap;
    if (factor > 1)
    {
        pixmap = scaleImage(factor).copy(m_fitpixmap.size().width() / 2 - (width / 2), m_fitpixmap.size().height() / 2 - (height / 2), width, height);
    }
    else
        pixmap = scaleImage(factor).copy(0, 0, width, height);
    this->setPixmap(pixmap);
//    this->setPixmap(m_fitpixmap.scaled(factor * m_fitpixmap.size()));
    //    this->resize(factor * m_fitpixmap.size());
}

void CustomLabel::setColor(QColor color)
{
    if ( color == Qt::red)
    {
        m_styleSheet = "QLabel { color : red; }";
        this->setStyleSheet("QLabel { color : red; }");

    }
    else if (color == Qt::white)
    {
        this->setStyleSheet("QLabel { color : white; }");
    }
}

void CustomLabel::setFontSize(int font_size)
{
//    int font_size = GetFontSize(ori_font_size);

    int calc_font_size = GetFontSize(font_size);
    QFont font = this->font();
    font.setPixelSize(calc_font_size);
    this->setFont(font);
//      m_styleSheet;
//    this->setStyleSheet(m_styleSheet);
}

QPixmap CustomLabel::scaleImage(double factor)
{
//    QPixmap pixmap;
    m_fitpixmap = m_fitpixmap.scaled(factor * size()/*, Qt::IgnoreAspectRatio, Qt::SmoothTransformation*/);
    return m_fitpixmap;
}

void CustomLabel::resizeEvent(QResizeEvent *event)
{
//    QFont font;
//    if(font.pointSizeF()>=FontSize::Maximum) //최소폰트 설정
//        font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.

//    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
//        font.setPointSizeF(FontSize::Minimum);
//    this->setFont(font); //설정된 폰트를 위젯에 적용
}
