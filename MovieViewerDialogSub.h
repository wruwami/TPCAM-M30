/**
 * @file MovieViewerDialogSub.h
 * @author wruwami (wruwami@naver.com)
 * @brief QtAVPlayer를 통해 구현한 동영상 플레이어 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MovieViewerDialogSub_H
#define MovieViewerDialogSub_H

#include <QDialog>

#include <QtAVPlayer/qavplayer.h>
#include <QtAVPlayer/qavvideoframe.h>
#include <QtAVPlayer/qavaudiooutput.h>
#include <QVideoWidget>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QMediaService>
#include <QMediaObject>
#include <QVideoRendererControl>

#include "FileFormat.h"
#include "QtAVPlayerHelper/mediaobject.h"
#include "QtAVPlayerHelper/mediaservice.h"
#include "QtAVPlayerHelper/videorenderer.h"
#include "QtAVPlayerHelper/videowidget.h"


namespace Ui {
class MovieViewerDialogSub;
}

/**
 * @brief  QtAVPlayer를 통해 구현한 동영상 플레이어 다이얼로그 클래스
 * 
 */
class QVideoWidget;
class QMediaPlayer;
class MovieViewerDialogSub : public QDialog
{
    Q_OBJECT

public:
    explicit MovieViewerDialogSub(AVFileFormat avFileFormat, QWidget *parent = 0);
    ~MovieViewerDialogSub();

private slots:
    void on_quitPushButton_clicked();


    void on_previousPushButton_clicked();

    void on_playPushButton_clicked();

    void on_nextPushButton_clicked();


    void on_printPushButton_clicked();

    void on_pausePushButton_clicked();
    void positionChanged(qint64 progress);
    void durationChanged(qint64 progress);
    void on_twoSpeedPushButton_clicked();

    void on_halfspeedPushButton_clicked();
    void seek(int seconds);
    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_sliderMoved(int position);

    void on_playPushButton_clicked(bool checked);

private:
    Ui::MovieViewerDialogSub*ui;
//    QVideoWidget* m_videoWidget;
//    QMediaPlayer* m_player;
    qint64 duration;

    QAVPlayer m_AVplayer;
//    VideoWidget m_VideoWidget;
    VideoWidget* m_pVideoWidget;
    VideoRenderer m_VRenderer;
    MediaObject* m_MediaObject;
//    MediaObject m_MediaObject(&m_VRenderer);
    QAVAudioOutput m_audioOutput;
    AVFileFormat m_avFileFormat;
    QVideoFrame m_videoFrame;
};

#endif // MovieViewerDialogSub_H
