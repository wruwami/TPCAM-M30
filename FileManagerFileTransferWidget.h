#ifndef FILEMANAGERFILETRANSFERWIDGET_H
#define FILEMANAGERFILETRANSFERWIDGET_H

#include <QWidget>

enum TransType
{
    FileType,
    FTPType,
};

namespace Ui {
class FileManagerFileTransferWidget;
}

class FileManagerFileTransferWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerFileTransferWidget(TransType, QWidget *parent = 0);
    ~FileManagerFileTransferWidget();
    void TransferFTP();
    void TransferFTP2();
    void TransferFile();
private:
    Ui::FileManagerFileTransferWidget *ui;
    int m_second = 0;
    int m_index = 0;
    int m_count = 0;
    QString m_file_name;
signals:
    void finished();
private slots:
//    void loadProgress(qint64 bytesSent, qint64 bytesTotal);    //Update progress bar

//    void replyFinished(QNetworkReply*);
protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);



};

#endif // FILEMANAGERFILETRANSFERWIDGET_H
