#ifndef FILEMANAGERFILETRANSFERDIALOG_H
#define FILEMANAGERFILETRANSFERDIALOG_H

#include <QDialog>

#include "FileFormat.h"

enum TransType
{
    FileType,
    FTPType,
};
class QNetworkReply;
namespace Ui {
class FileManagerFileTransferDialog;
}

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
private slots:
    void loadProgress(qint64 bytesSent, qint64 bytesTotal);    //Update progress bar

    void replyFinished(QNetworkReply*);
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // FILEMANAGERFILETRANSFERDIALOG_H
