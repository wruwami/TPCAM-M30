#include "CustomZoomLabel.h"

#include "qdir.h"
#include <QMouseEvent>

#define DEFAULT_PATH    "images"

#include "FontSize.h"
#include "FileManager.h"

CustomZoomLabel::CustomZoomLabel(QWidget *parent) : QLabel(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//void CustomZoomLabel::setIconImage(QString path_name, QString file_name)
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
void CustomZoomLabel::setImageFromAvi(QString file_path, QSize size)
{
    m_pixmap.load(file_path);
    QPixmap fitpixmap = m_pixmap.scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(fitpixmap);
//    this->setScaledContents(true);
}

void CustomZoomLabel::setImage(QString file_path, QSize size)
{
    m_pixmap.load(file_path);
    m_fitpixmap = m_pixmap.scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_fitpixmap);
//    this->setScaledContents(true);
}

void CustomZoomLabel::resizeImage(QSize size)
{
//    m_pixmap.load(file_path);
    m_fitpixmap = m_pixmap.scaled(size.width(), size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_fitpixmap);
//    this->setScaledContents(true);
}

void CustomZoomLabel::setImage(QPixmap pixmap)
{
    m_pixmap = pixmap;
    m_fitpixmap = m_pixmap.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_fitpixmap);
//    this->setScaledContents(true);
}

void CustomZoomLabel::setImage(QString path_name, QString file_name)
{
    QDir qdir;
    QString file_full_path;
    file_full_path = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;


    m_pixmap.load(file_full_path);
//    QPixmap fitpixmap=pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_pixmap);
//    this->setScaledContents(true);
}

void CustomZoomLabel::setImage(QString path_name, QString file_name, QSize size)
{
    QDir qdir;
    QString file_full_path;
    file_full_path = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;


    m_pixmap.load(file_full_path);
//    QPixmap fitpixmap=pixmap.scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(m_pixmap);
    //    this->setScaledContents(true);
}

void CustomZoomLabel::removeImage()
{
//    QPixmap pixmap;
    m_pixmap = QPixmap();
    m_fitpixmap = QPixmap();
    this->setPixmap(m_pixmap);
}

QPixmap CustomZoomLabel::scaleImage(double factor)
{
    return m_pixmap.scaled(factor * size());
}


void CustomZoomLabel::resizeEvent(QResizeEvent *event)
{
//    QFont font;
//    if(font.pointSizeF()>=FontSize::Maximum) //최소폰트 설정
//        font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.

//    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
//        font.setPointSizeF(FontSize::Minimum);
//    this->setFont(font); //설정된 폰트를 위젯에 적용
}

void CustomZoomLabel::mousePressEvent(QMouseEvent *event)
{
    m_isZoom = !m_isZoom;

    if (m_isZoom)
    {
        QRect rect(event->x(), event->y(), width(), height());
        setPixmap(scaleImage(2).copy(rect));
    }
    else
    {
        setPixmap(m_fitpixmap);
    }

}
