#include "CustomPushButton.h"

#include "FontSize.h"
#include <QDir>

#define DEFAULT_PATH    "images"

CustomPushButton::CustomPushButton(QWidget *parent) : QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CustomPushButton::setImage(QString path_name, QString file_name)
{
    // icon 방식
    // 추후 icon방식이 적절하지 않으면 background-image 방식으로 변경하여야 함.
    QDir qdir;
    QString file_full_path;
#ifdef Q_OS_WIN
    file_full_path = qdir.absolutePath() + "\\" + DEFAULT_PATH + "\\" + path_name + "\\" + file_name;
#else   /*Q_OS_LINUX*/
    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;
#endif
    this->setIcon(QIcon(file_full_path));
}

void CustomPushButton::resizeEvent(QResizeEvent *event)
{
    QFont font;
    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
        font.setPointSizeF(FontSize::Minimum);
    this->setFont(font); //설정된 폰트를 위젯에 적용
}
