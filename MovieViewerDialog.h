#ifndef MOVIEVIEWERDIALOG_H
#define MOVIEVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class MovieViewerDialog;
}

class QVideoWidget;
class QMediaPlayer;
class MovieViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MovieViewerDialog(QString file_path, QWidget *parent = 0);
    ~MovieViewerDialog();

private slots:
    void on_quitPushButton_clicked();

    void on_firstPushButton_clicked();

    void on_previousPushButton_clicked();

    void on_playPushButton_clicked();

    void on_nextPushButton_clicked();

    void on_lastPushButton_clicked();

    void on_printPushButton_clicked();

private:
    Ui::MovieViewerDialog*ui;
    QVideoWidget* m_videoWidget;
    QMediaPlayer* m_player;
};

#endif // MOVIEVIEWERDIALOG_H
