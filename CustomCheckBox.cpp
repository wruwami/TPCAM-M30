#include "CustomCheckBox.h"

#include "qdir.h"

#include "FontSize.h"
#include "WidgetSize.h"
#include "FileManager.h"

CustomCheckBox::CustomCheckBox(QWidget *parent) : QCheckBox(parent)
{
    QDir dir;

    QString styleSheet(QString("QCheckBox::indicator { width:%0px; height: %1px; } QCheckBox::indicator:checked \
    { \
      image: url(%2/images/Date_time/checked.bmp); \
    }\
     \
    QCheckBox::indicator:unchecked \
    { \
      image: url(%2/images/Date_time/unchecked.bmp); \
    } \
    ").arg(GetWidgetSize(QSize(88, 88)).width()).arg(GetWidgetSize(QSize(88, 88)).height()).arg(GeteMMCPath()));
    // "QCheckBox::indicator { width:50px; height: 50px; }"
//    this->resize();

    this->setStyleSheet(styleSheet);

                       this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CustomCheckBox::setFontSize(int font_size)
{
    int calc_font_size = GetFontSize(font_size);
    QFont font = this->font();
    font.setPixelSize(calc_font_size);
    this->setFont(font);
}



void CustomCheckBox::resizeEvent(QResizeEvent *event)
{
//    QFont font;
//    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
//    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
//        font.setPointSizeF(FontSize::Minimum);
//    this->setFont(font); //설정된 폰트를 위젯에 적용
}
