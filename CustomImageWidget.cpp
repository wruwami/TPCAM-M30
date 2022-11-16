#include "CustomImageWidget.h"

#include <QFile>
#include <QDir>
#include <QPainter>

#define DEFAULT_PATH    "images"

CustomImageWidget::CustomImageWidget(QWidget *parent) : QWidget(parent)
{
    QFile file(":/style/customImageButton.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    setStyleSheet(styleSheet);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CustomImageWidget::setImage(QString path_name, QString file_name)
{
    QDir qdir;
    QString file_full_path;

    file_full_path = qdir.absolutePath() + "/" + DEFAULT_PATH + "/" + path_name + "/" + file_name;

    this->setAutoFillBackground(true);    //Widget When adding background pictures , This must be true .
    m_pixmap.load(file_full_path);
//    QPixmap fitpixmap=m_pixmap.scaled(1200, 1200).scaled(config->mainWindowW,config->mainWindowH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(m_pixmap));
//    this->setPalette(palette);
}

void CustomImageWidget::paintEvent(QPaintEvent *e)
{
    int width = size().width();
    int height = size().height();
    QPainter painter(this);
    painter.drawPixmap(1, 1, m_pixmap.scaled(QSize(width-2,height-2)));
    QWidget::paintEvent(e);
}
