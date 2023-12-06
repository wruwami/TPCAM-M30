/**
 * @file StillImageViewerDialog.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일 매니저 스틸 이미지 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STILLIMAGEVIEWERDIALOG_H
#define STILLIMAGEVIEWERDIALOG_H

#include "FileFormat.h"

#include <QDialog>

namespace Ui {
class StillImageViewerDialog;
}

class StillImageViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StillImageViewerDialog(AVFileFormat avFileFormat, QWidget *parent = 0);
    ~StillImageViewerDialog();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_quitPushButton_clicked();

    void on_plusPushButton_clicked();

    void on_minusPushButton_clicked();

    void on_originPushButton_clicked();
    
    void on_printPushButton_clicked();

private:
    Ui::StillImageViewerDialog*ui;
    AVFileFormat m_avFileFormat;
    QString m_file_path;
    double m_factor = 1;
};

#endif // STILLIMAGEVIEWERDIALOG_H
