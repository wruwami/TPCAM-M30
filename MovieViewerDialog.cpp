#include "MovieViewerDialog.h"
#include "ui_MovieViewerDialog.h"

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QSlider>

#include "StringLoader.h"
#include "WidgetSize.h"
#include "DateFormatManager.h"

MovieViewerDialog::MovieViewerDialog(AVFileFormat avFileFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieViewerDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0,0, 1600, 960)));

    m_player = new QMediaPlayer(this);
    m_videoWidget = new QVideoWidget(this);
    ui->verticalLayout->insertWidget(0, m_videoWidget, 390);
    m_videoWidget->show();
    m_player->setVideoOutput(m_videoWidget);

    QUrl url = QUrl::fromLocalFile(avFileFormat.file_path);
    m_player->setMedia(url);

    ui->horizontalSlider->setRange(0, m_player->duration() / 1000);
//    ui->moveViewerLabel->setText(LoadString("IDS_MOVIE_VIEWER"));

    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->playPushButton->setText(LoadString("IDS_PLAY"));
    ui->pausePushButton->setText(LoadString("IDS_PAUSE"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));

    ui->laserSpeedLabel->setText(QString("C %1km/h").arg(avFileFormat.captureSpeedLimit));
    ui->laserDistanceLabel->setText(QString("%1m").arg(avFileFormat.distance));
    ui->indexLabel->setText("[" + QString(avFileFormat.index).mid(0,5) + "]");
    ui->dateLabel->setText(GetDate(avFileFormat.date));
    ui->timeLabel->setText(QString(avFileFormat.time).mid(0,6));
    ui->rtLabel->setText("RT - - - km/h, - - - - -m");



    ui->horizontalSlider->setRange(0, m_player->duration() / 1000);

    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
}

MovieViewerDialog::~MovieViewerDialog()
{
    delete m_videoWidget;
    delete m_player;
    delete ui;
}

void MovieViewerDialog::on_quitPushButton_clicked()
{
    accept();
}

void MovieViewerDialog::on_previousPushButton_clicked()
{
    m_player->setPosition(m_player->position() - duration);
}

void MovieViewerDialog::on_playPushButton_clicked()
{
    m_player->play();
}

void MovieViewerDialog::on_nextPushButton_clicked()
{
    m_player->setPosition(m_player->position() + duration);
}

void MovieViewerDialog::on_printPushButton_clicked()
{

}

void MovieViewerDialog::on_pausePushButton_clicked()
{
    m_player->pause();
}

void MovieViewerDialog::positionChanged(qint64 progress)
{
    if (!ui->horizontalSlider->isSliderDown()) {
        ui->horizontalSlider->setValue(progress / 1000);
    }

}

void MovieViewerDialog::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    ui->horizontalSlider->setMaximum(duration / 1000);
}

void MovieViewerDialog::on_twoSpeedPushButton_clicked()
{
    m_player->setPlaybackRate(2);
}

void MovieViewerDialog::on_halfspeedPushButton_clicked()
{
    m_player->setPlaybackRate(0.5);
}

void MovieViewerDialog::seek(int seconds)
{
    m_player->setPosition(seconds * 1000);
}
