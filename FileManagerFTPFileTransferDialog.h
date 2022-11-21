#ifndef FILEMANAGERFTPFILETRANSFERDIALOG_H
#define FILEMANAGERFTPFILETRANSFERDIALOG_H

#include <QDialog>

namespace Ui {
class FileManagerFTPFileTransferDialog;
}

class FileManagerFTPFileTransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerFTPFileTransferDialog(QWidget *parent = 0);
    ~FileManagerFTPFileTransferDialog();

private:
    Ui::FileManagerFTPFileTransferDialog *ui;
};

#endif // FILEMANAGERFTPFILETRANSFERDIALOG_H
