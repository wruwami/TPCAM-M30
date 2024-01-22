/**
 * @file FileManagerWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일매니저 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include <QHeaderView>

#include "FileFormat.h"
#include "StorageManager.h"

#include "QtAVPlayerHelper/mediaobject.h"
#include "QtAVPlayerHelper/mediaservice.h"
#include "QtAVPlayerHelper/videorenderer.h"
#include "QtAVPlayerHelper/videowidget.h"

namespace Ui {
class FileManagerWidget;
}

class QPushButton;
class QAVPlayer;
class VideoWidget;
//class QMediaPlayer;
class QVideoWidget;
/**
 * @brief 파일매니저 위젯 클래스
 * 
 */
class FileManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerWidget(QWidget *parent = 0);
    ~FileManagerWidget();
public:
/**
 * @brief 파일 매니저 홈 버튼
 * 
 */
    QPushButton* m_pHomePushButton;
private:
    Ui::FileManagerWidget *ui;
    /**
     * @brief 모드 변수(I,V,A,M,S)
     * 
     */
    int m_nMode;
    // QWidget interface
    /**
     * @brief 현재 가지고 있는 파일 포맷 리스트
     * 
     */
    QList<AVFileFormat> m_avFileFormatList;
    /**
     * @brief 전에 가지고 있던 파일 포맷 리스트
     * 
     */
    QList<AVFileFormat> m_avPreviousFileFormatList;
    /**
     * @brief 현재 선택된 파일의 파일 포맷
     * 
     */
    AVFileFormat m_currentAVFileFormat;
    /**
     * @brief 테이블 파일 선택 인덱스
     * 
     */
    int m_AVFileFormatIndex = 0;
//    QVideoWidget *m_videoWidget;
/**
 * @brief 비디오 위젯
 * 
 */
    VideoWidget* m_pVideoWidget;
    /**
     * @brief 비디오 플레이 클래스 변수
     * 
     */
    QAVPlayer* m_player;
    /**
     * @brief 현재 선택된 날짜,시간 변수
     * 
     */
    QString m_dateTime;
    StorageManager m_sdcardManager;
    /**
     * @brief 일반 프린터, 열전사 프린터 선택 변수
     * 
     */
    bool m_bA4Print = false;
    /**
     * @brief 이미지 변수
     * 
     */
    QImage m_image;
private:
/**
 * @brief 현재 선택된 날짜의 파일 리스트를 초기화한다.
 * 
 */
    void setTableContent();
    /**
     * @brief 현재 파일 포맷값을 열전사 포맷으로 전환한다.
     * 
     */
    void convertValue();
    /**
     * @brief 파일 리스트를 초기화한다.
     * 
     */
    void initTable();
//    void printA4();
/**
 * @brief 프린트 기능을 활성화 한다.
 * 
 */
    void SetPrintEnabled();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
private slots:
    void on_deletePushButton_clicked();
//    void on_tableWidget_clicked(const QModelIndex &index);
    void on_searchPushButton_clicked();
    void on_zoomPlayPushButton_clicked();
    void on_sharePushButton_clicked();
    void on_movePushButton_clicked();
    void on_printPushButton_clicked();
    void on_connectPushButton_clicked();
    void on_percentPushButton_clicked();
    void on_ImageVideoComboBox_currentIndexChanged(int index);
    void on_datePushButton_clicked();
    void on_firstPushButton_clicked();
    void on_previousPushButton_clicked();
    void on_nextPushButton_clicked();
    void on_lastPushButton_clicked();
//    void on_tableWidget_cellClicked(int row, int column);
    void on_tableWidget_cellClicked(int row, int column);
};

#endif // FILEMANAGERWIDGET_H
