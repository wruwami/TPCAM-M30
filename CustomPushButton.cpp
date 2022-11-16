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
//#ifdef Q_OS_WIN
//    file_full_path = qdir.absolutePath() + "\\" + DEFAULT_PATH + "\\" + path_name + "\\" + file_name;
//#else   /*Q_OS_LINUX*/
    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;
//#endif

#if 1
    m_pixmap.load(file_full_path);
    setAutoFillBackground(true);
    QSize ssize = size();
    this->sizeHint();
    m_icon = QIcon(m_pixmap);

    m_pixmap = m_pixmap.scaled(size().width(), size().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setIcon(m_icon);
    this->setIconSize(QSize(size().width(), size().height()));
#else
    // background-image 방식
//    QUrl url(file_full_path);
//    url.set
//
    this->setStyleSheet(QString("QPushButton { \
                                color: black; \
                                background-color: white; \
                                border-width: 1px; \
                                border-color: blue; \
                                border-style: solid; \
                                background-image: url(%0);\
                                background-repeat = no-repeat;\
                            }\
                            QPushButton:pressed { \
                                border-color: red; \
                            }").arg(file_full_path));


//    m_pixmap.load(file_full_path);
//    update();
//    QPalette pal = QPalette();
//    pal.setBrush(QPalette::Background, QBrush(pixmap));
//    this->setAutoFillBackground(true);
//    this->setPalette(pal);
//    this->update();



//    this->setStyleSheet(QString("QPushButton::BorderImage { \
//                                width: 180; height: 180 \
//                        border { left: 30; top: 30; right: 30; bottom: 30 }\
//                        horizontalTileMode: BorderImage.Stretch\
//                        verticalTileMode: BorderImage.Stretch\
//                        source: %0}));\
//                        }").arg(file_full_path));

#endif
}

void CustomPushButton::resizeEvent(QResizeEvent *event)
{
    QFont font;
    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
        font.setPointSizeF(FontSize::Minimum);
    this->setFont(font); //설정된 폰트를 위젯에 적용

//    this->setIconSize(QSize(this->size().width(), this->size().height()));
}

void CustomPushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    QRect rec=contentsRect();
    rec.adjust(0,8,-0,-10);     // margins specific to MacOs

    int w=rec.size().width();
    int h=rec.size().height();
    QSize _size(w,h);
    QPoint top=rec.topLeft();
//    top.setX((rec.width()-h)/2);

    // draw the outline rec of the button to visualise the real size of the widget !
    painter.drawRect(rect().adjusted(0,0,-1,-1));

    painter.drawPixmap(QRect(top,_size), m_icon.pixmap(_size));

//    qDebug()<<QRect(top,size)<<contentsRect();
}
