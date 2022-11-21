#ifndef FILEMANAGERSNAPSHOTDIALOG_H
#define FILEMANAGERSNAPSHOTDIALOG_H

#include <QDialog>

namespace Ui {
class FileManagerSnapShotDialog;
}

class FileManagerSnapShotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerSnapShotDialog(QWidget *parent = 0);
    ~FileManagerSnapShotDialog();

private:
    Ui::FileManagerSnapShotDialog *ui;
};

#endif // FILEMANAGERSNAPSHOTDIALOG_H
