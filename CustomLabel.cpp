#include "CustomLabel.h"

#include "qdir.h"

#define DEFAULT_PATH    "images"

#include "FontSize.h"

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

void CustomLabel::setImage(QString path_name, QString file_name)
{
    QDir qdir;
    QString file_full_path;
    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;

    QPixmap pixmap;
    pixmap.load(file_full_path);
//    QPixmap fitpixmap=pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(pixmap);
//    this->setScaledContents(true);
}

void CustomLabel::setImage(QString path_name, QString file_name, QSize size)
{
    QDir qdir;
    QString file_full_path;
    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;

    QPixmap pixmap;
    pixmap.load(file_full_path);
//    QPixmap fitpixmap=pixmap.scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(pixmap);
//    this->setScaledContents(true);
}


void CustomLabel::resizeEvent(QResizeEvent *event)
{
    QFont font;
    if(font.pointSizeF()>=FontSize::Maximum) //최소폰트 설정
        font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.

    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
        font.setPointSizeF(FontSize::Minimum);
    this->setFont(font); //설정된 폰트를 위젯에 적용
}
