/**
 * @file MovieViewerDialog.h
 * @author wruwami (wruwami@naver.com)
 * @brief QMediaPlayer를 통해 구현한 동영상 플레이어 다이얼로그(현재 사용안함)
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MOVIEVIEWERDIALOG_H
#define MOVIEVIEWERDIALOG_H

#include <QDialog>

#include "FileFormat.h"

namespace Ui {
class MovieViewerDialog;
}

class QVideoWidget;
class QMediaPlayer;
/**
 * @brief QMediaPlayer를 통해 구현한 동영상 플레이어 다이얼로그 클래스(현재 사용안함)
 * 
 */
class MovieViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MovieViewerDialog(AVFileFormat avFileFormat, QWidget *parent = 0);
    ~MovieViewerDialog();

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
private:
    Ui::MovieViewerDialog*ui;
    QVideoWidget* m_videoWidget;
    QMediaPlayer* m_player;
    qint64 duration;
};

#endif // MOVIEVIEWERDIALOG_H
