#include "MovieViewerDialog.h"
#include "ui_MovieViewerDialog.h"

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QSlider>

#include "StringLoader.h"
#include "WidgetSize.h"

MovieViewerDialog::MovieViewerDialog(QString file_path, QWidget *parent) :
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

    QUrl url = QUrl::fromLocalFile(file_path);
    m_player->setMedia(url);

//    ui->moveViewerLabel->setText(LoadString("IDS_MOVIE_VIEWER"));

    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->playPushButton->setText(LoadString("IDS_PLAY"));
    ui->pausePushButton->setText(LoadString("IDS_PAUSE"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));

    connect(ui->horizontalSlider, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(ui->horizontalSlider, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
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

}

void MovieViewerDialog::on_playPushButton_clicked()
{
    m_player->play();
}

void MovieViewerDialog::on_nextPushButton_clicked()
{

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

void MovieViewerDialog::durationChanged(qint64 progress)
{

}

void MovieViewerDialog::on_twoSpeedPushButton_clicked()
{

}

void MovieViewerDialog::on_halfspeedPushButton_clicked()
{

}
