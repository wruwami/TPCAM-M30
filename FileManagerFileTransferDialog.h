#ifndef FILEMANAGERFILETRANSFERDIALOG_H
#define FILEMANAGERFILETRANSFERDIALOG_H

#include <QDialog>

#include "FileFormat.h"

enum Type
{
    FileType,
    FTPType,
};

namespace Ui {
class FileManagerFileTransferDialog;
}

class FileManagerFileTransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerFileTransferDialog(QList<AVFileFormat> avFileFormatList, Type type, QWidget *parent = 0);
    ~FileManagerFileTransferDialog();
private:
    void TransferFTP();
private:
    Ui::FileManagerFileTransferDialog *ui;
    QList<AVFileFormat> m_avFileFormatList;
    int m_second = 0;
private slots:
    void loadProgress(qint64 bytesSent, qint64 bytesTotal);    //Update progress bar
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // FILEMANAGERFILETRANSFERDIALOG_H
