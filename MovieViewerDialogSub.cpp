#include "MovieViewerDialogSub.h"
#include "ui_MovieViewerDialogSub.h"

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QSlider>

#include "StringLoader.h"
#include "WidgetSize.h"
#include "DateFormatManager.h"
#include "SpeedUnitManager.h"

MovieViewerDialogSub::MovieViewerDialogSub(AVFileFormat avFileFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieViewerDialogSub)
{
    ui->setupUi(this);

    m_pVideoWidget = new VideoWidget;
    m_MediaObject = new MediaObject(&m_VRenderer);
//    m_VideoWidget.setMediaObject(m_MediaObject);
    m_pVideoWidget->setMediaObject(m_MediaObject);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0,0, 1600, 960)));

//    m_player = new QMediaPlayer(this);
//    m_videoWidget = new QVideoWidget(this);
    ui->verticalLayout->insertWidget(0, m_pVideoWidget, 390);
    m_pVideoWidget->show();
//    m_player->setVideoOutput(m_videoWidget);

    QUrl url = QUrl::fromLocalFile(avFileFormat.file_path);
    QString file = avFileFormat.file_path;
    m_AVplayer.setSource(file);


//    m_player->setMedia(url);

//    ui->horizontalSlider->setRange(0, m_player->duration() / 1000);
    ui->horizontalSlider->setRange(0, m_AVplayer.duration() / 1000);
//    ui->moveViewerLabel->setText(LoadString("IDS_MOVIE_VIEWER"));

    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->quitPushButton->setFontSize(23);
    ui->playPushButton->setText(LoadString("IDS_PLAY"));
    ui->playPushButton->setFontSize(23);
    ui->pausePushButton->setText(LoadString("IDS_PAUSE"));
    ui->pausePushButton->setFontSize(23);
    ui->printPushButton->setText(LoadString("IDS_PRINT"));
    ui->printPushButton->setFontSize(23);

    QString captureSpeedLimit = QString::number(avFileFormat.captureSpeedLimit.toInt());
    ui->laserSpeedLabel->setText(QString("C %1%2").arg(captureSpeedLimit).arg(speedUnitValue()));
    ui->laserSpeedLabel->setFontSize(15);
//    ui->laserSpeedLabel->setFontSize(23);
    QString distance = QString::number(avFileFormat.distance.toInt());
    ui->laserDistanceLabel->setText(QString("%1%2").arg(distance).arg(distanceValue()));
    ui->laserDistanceLabel->setFontSize(15);
//    ui->laserDistanceLabel->setFontSize(23);
    ui->indexLabel->setText("[" + QString(avFileFormat.index).mid(0,5) + "]");
    ui->indexLabel->setFontSize(15);
//    ui->indexLabel->setFontSize(23);
    ui->dateLabel->setText(GetDate(avFileFormat.date));
    ui->dateLabel->setFontSize(15);
//    ui->dateLabel->setFontSize(23);
    ui->timeLabel->setText(QString(avFileFormat.time).mid(0,2) + ":" + QString(avFileFormat.time).mid(2,2) + ":" + QString(avFileFormat.time).mid(4,2));
    ui->timeLabel->setFontSize(15);
//    ui->timeLabel->setFontSize(23);
    QString captureSpeed = QString::number(avFileFormat.captureSpeedLimit.mid(1,4).toInt());
    ui->rtLabel->setText(QString("RT %0 %1, %2 %3").arg(captureSpeed).arg(speedUnitValue()).arg(distance).arg(distanceValue()));
    ui->rtLabel->setFontSize(15);


//    ui->horizontalSlider->setRange(0, m_player->duration() / 1000);
    ui->horizontalSlider->setRange(0, m_AVplayer.duration() / 1000);

    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(&m_AVplayer, SIGNAL(sendPositionByFrame(qint64)), SLOT(positionChanged(qint64)));
    connect(&m_AVplayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));

    QObject::connect(&m_AVplayer, &QAVPlayer::audioFrame, &m_AVplayer, [this](const QAVAudioFrame &frame) { m_audioOutput.play(frame); });

    QObject::connect(&m_AVplayer, &QAVPlayer::videoFrame, &m_AVplayer, [&](const QAVVideoFrame &frame) {
        if (m_VRenderer.m_surface == nullptr)
            return;

        QVideoFrame videoFrame = frame.convertTo(AV_PIX_FMT_RGB32);
        if (!m_VRenderer.m_surface->isActive() || m_VRenderer.m_surface->surfaceFormat().frameSize() != videoFrame.size()) {
            QVideoSurfaceFormat f(videoFrame.size(), videoFrame.pixelFormat(), videoFrame.handleType());
            m_VRenderer.m_surface->start(f);
        }
        if (m_VRenderer.m_surface->isActive())
            m_VRenderer.m_surface->present(videoFrame);
    });


    //temp
    ui->previousPushButton->setEnabled(false);
    ui->nextPushButton->setEnabled(false);
}

MovieViewerDialogSub::~MovieViewerDialogSub()
{
    delete m_pVideoWidget;
//    delete m_videoWidget;
//    delete m_player;
    delete m_MediaObject;

    delete ui;
}

void MovieViewerDialogSub::on_quitPushButton_clicked()
{
    accept();
}

void MovieViewerDialogSub::on_previousPushButton_clicked()
{
//    m_player->setPosition(m_player->position() - duration);
    m_AVplayer.setPosition(m_AVplayer.position() - duration);
}

void MovieViewerDialogSub::on_playPushButton_clicked()
{
//    m_player->play();
    m_AVplayer.play();
}

void MovieViewerDialogSub::on_nextPushButton_clicked()
{
//    m_player->setPosition(m_player->position() + duration);
    m_AVplayer.setPosition(m_AVplayer.position() + duration);
}

void MovieViewerDialogSub::on_printPushButton_clicked()
{

}

void MovieViewerDialogSub::on_pausePushButton_clicked()
{
//    m_player->pause();
    m_AVplayer.pause();
}

void MovieViewerDialogSub::positionChanged(qint64 progress)
{
    if (!ui->horizontalSlider->isSliderDown()) {
        ui->horizontalSlider->setValue(progress / 1000);
    }

}

void MovieViewerDialogSub::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    ui->horizontalSlider->setMaximum(duration / 1000);
}

void MovieViewerDialogSub::on_twoSpeedPushButton_clicked()
{
//    m_player->setPlaybackRate(2);
    m_AVplayer.setSpeed(2);
}

void MovieViewerDialogSub::on_halfspeedPushButton_clicked()
{
//    m_player->setPlaybackRate(0.5);
    m_AVplayer.setSpeed(0.5);
}

void MovieViewerDialogSub::seek(int seconds)
{
//    m_player->setPosition(seconds * 1000);
    m_AVplayer.setPosition(seconds * 1000);
}

void MovieViewerDialogSub::on_horizontalSlider_valueChanged(int value)
{

}

void MovieViewerDialogSub::on_horizontalSlider_sliderMoved(int position)
{
    m_AVplayer.setPosition(position * 1000);
}
