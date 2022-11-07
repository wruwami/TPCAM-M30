#include "CustomCheckBox.h"

#include "FontSize.h"

CustomCheckBox::CustomCheckBox(QWidget *parent) : QCheckBox(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CustomCheckBox::resizeEvent(QResizeEvent *event)
{
    QFont font;
    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
        font.setPointSizeF(FontSize::Minimum);
    this->setFont(font); //설정된 폰트를 위젯에 적용
}
