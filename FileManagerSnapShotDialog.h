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
    void addListItem(QString str);
private slots:
    void on_backPushButton_clicked();

private:
    Ui::FileManagerSnapShotDialog *ui;


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // FILEMANAGERSNAPSHOTDIALOG_H
