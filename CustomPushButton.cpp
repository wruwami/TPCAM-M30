#include "CustomPushButton.h"

#include "qdir.h"
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QFont>

#include "FontSize.h"
#include "ImageSize.h"
#include "FileManager.h"
#include "WidgetSize.h"

#define DEFAULT_PATH    "images"

CustomPushButton::CustomPushButton(QWidget *parent) : QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
//    m_size = size();
}

void CustomPushButton::setImage(QString path_name, QString file_name)
{
    // icon 방식
    // 추후 icon방식이 적절하지 않으면 background-image 방식으로 변경하여야 함.
    setMinimumSize(QSize(0, 0));
    QDir qdir;
    QString file_full_path;
//#ifdef Q_OS_WIN
//    file_full_path = qdir.absolutePath() + "\\" + DEFAULT_PATH + "\\" + path_name + "\\" + file_name;
//#else   /*Q_OS_LINUX*/
    file_full_path = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;
//#endif

#if 1
    m_pixmap.load(file_full_path);
//    m_pixmap = m_pixmap.scaled(size().width(), size().height(), Qt::KeepAspectRatioByExpanding);
    m_icon = QIcon(m_pixmap);
    this->setIcon(m_icon);
//    this->setIconSize(m_icon.availableSizes().first());
//    QSize _size = QSize(size().width()*2, size().height()*2);
//    this->setIconSize(_size);
//    qDebug() << m_pixmap.size();
//    qDebug() << size();

//    this->setIconSize(m_pixmap.size());
//    this->setIconSize(QSize(size().width(), size().height()));
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

void CustomPushButton::setImage(QString path_name, QString file_name, QSize size)
{
    // icon 방식
    // 추후 icon방식이 적절하지 않으면 background-image 방식으로 변경하여야 함.
    QDir qdir;
    QString file_full_path;
//#ifdef Q_OS_WIN
//    file_full_path = qdir.absolutePath() + "\\" + DEFAULT_PATH + "\\" + path_name + "\\" + file_name;
//#else   /*Q_OS_LINUX*/
    file_full_path = GeteMMCPath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;
//#endif

#if 1
    m_pixmap.load(file_full_path);


    m_icon = QIcon(m_pixmap);
//    QSize _size = size();
//    m_pixmap = m_pixmap.scaled(_size.width, _size.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setIcon(m_icon);
    this->setIconSize(size);

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

void CustomPushButton::setFontSize(int font_size)
{
    int calc_font_size = GetFontSize(font_size);
    QFont font = this->font();
    font.setPixelSize(calc_font_size);
    this->setFont(font);
}

//void CustomPushButton::setText(const QString text)
//{
//    max = maximumSize();
//    min = minimumSize();
//    setMinimumSize(size());
//    setMaximumSize(size());
//    settingText = true;

//    QPushButton::setText(text);
//}

void CustomPushButton::resizeEvent(QResizeEvent *event)
{
//    QPushButton::resizeEvent(event);
//    if(settingText){
//        setMinimumSize(min);
//        setMaximumSize(max);
//        settingText = false;
//    }

    //    QFont font;
//    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
//    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
//        font.setPointSizeF(FontSize::Minimum);
//    this->setFont(font); //설정된 폰트를 위젯에 적용

//    m_size = event->size();

//    m_pixmap.size();

//    qDebug() << m_size * (float)m_pixmap.width() / (float)width();
//    m_ratio = (float)m_pixmap.width() / (float)width();
//    this->setIconSize(m_size * m_ratio);
//    qDebug() << m_size;
}

void CustomPushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);

    // draw the outline rec of the button to visualise the real size of the widget !
//    QRect adjusted = QRect(rect().topLeft(), m_size);
//    QRect adjusted = m_size;
//    qDebug() << "adjusted.size()" <<adjusted.size();
//    qDebug() << "adjusted.rect()" << adjusted;

//    QRect adjusted = rect();//.adjusted(0,0,0,-1);
//    event->x
    QRect adjusted = event->rect().adjusted(2,2,-2,-2);
//    QRect adjusted = m_pixmap.rect().adjusted(1,1,-1,-1);
//    painter.drawRect(adjusted);
//    m_pixmap = m_pixmap.scaled(m_size);
//    painter.drawPixmap(adjusted, m_icon.pixmap(adjusted.size()));
    painter.drawPixmap(adjusted, m_icon.pixmap(adjusted.size()));

//    painter.drawPixmap(adjusted, m_pixmap);
//    qDebug() << "icon.size()" << m_icon.size();


//    QRect adjusted = contentsRect().adjusted(1,1,-2,-2);
//    painter.drawRect(adjusted);
//    painter.drawPixmap(adjusted, m_icon.pixmap(adjusted.size()));
//    qDebug() << m_size;
//    qDebug() << m_icon.size();
}
