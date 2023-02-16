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

    m_player = new QMediaPlayer;
    m_videoWidget = new QVideoWidget;
    ui->horizontalLayout_5->addWidget(m_videoWidget);
    m_videoWidget->show();

    m_player->setMedia(QUrl::fromLocalFile(file_path));

//    ui->moveViewerLabel->setText(LoadString("IDS_MOVIE_VIEWER"));

    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->playPushButton->setText(LoadString("IDS_PLAY"));
    ui->pausePushButton->setText(LoadString("IDS_PAUSE"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));
}

MovieViewerDialog::~MovieViewerDialog()
{
    delete ui;
}

void MovieViewerDialog::on_quitPushButton_clicked()
{
    accept();
}

void MovieViewerDialog::on_firstPushButton_clicked()
{

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

void MovieViewerDialog::on_lastPushButton_clicked()
{

}

void MovieViewerDialog::on_printPushButton_clicked()
{

}
