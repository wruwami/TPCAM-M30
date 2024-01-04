/**
 * @file FileManagerFileTransferDialog.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일매니저에서 사용되는 FTP, USB 전송을 표시하는 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILEMANAGERFILETRANSFERDIALOG_H
#define FILEMANAGERFILETRANSFERDIALOG_H

#include <QDialog>
#include <QSharedPointer>
#include <QThread>

#include "FileTransThread.h"
#include "FtpTransThread2.h"

enum TransType
{
    FileType,
    FTPType,
};

class CustomPushButton;
class QNetworkReply;
namespace Ui {
class FileManagerFileTransferDialog;
}

/**
 * @brief 열전사 프린터 연결 실패 시 메시지 보여주는 다이얼로그 클래스
 * 
 */
class FileManagerFileTransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerFileTransferDialog(TransType type, QWidget *parent = 0);
    ~FileManagerFileTransferDialog();
private:
    void TransferFTP();
    void TransferFile();
private:
    Ui::FileManagerFileTransferDialog *ui;
    int m_second = 0;
    int m_index = 0;
    int m_count = 0;
    QString m_file_name;
//    QSharedPointer<FileTransThread> m_FileTransThread;
//    QSharedPointer<FtpTransThread2> m_FtpTransThread;
    FileTransThread* m_FileTransThread = nullptr;
    FtpTransThread2* m_FtpTransThread = nullptr;
    CustomPushButton* m_pClosePushButton = nullptr;
    TransType m_type;
signals:
    void finished();
private slots:
    void setValue(int);
    void setMaximum(int);
    void setFileNameText(QString);
    void setFileCountText(QString);
    void closeThread();
//    void loadProgress(qint64 bytesSent, qint64 bytesTotal);    //Update progress bar

//    void replyFinished(QNetworkReply*);
protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // FILEMANAGERFILETRANSFERDIALOG_H
