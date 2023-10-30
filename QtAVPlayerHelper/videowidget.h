#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include <QtAVPlayer/qavplayer.h>
#include <QtAVPlayer/qavvideoframe.h>
#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QApplication>
#include <QDebug>

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QMediaService>
#include <QMediaObject>
#include <QVideoRendererControl>

class VideoWidget : public QVideoWidget
{
public:
    bool setMediaObject(QMediaObject *object) override
    {
        return QVideoWidget::setMediaObject(object);
    }
};

#endif // VIDEOWIDGET_H
