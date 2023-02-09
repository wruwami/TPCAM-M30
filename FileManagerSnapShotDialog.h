#ifndef FILEMANAGERSNAPSHOTDIALOG_H
#define FILEMANAGERSNAPSHOTDIALOG_H

#include <QDialog>

class QListWidgetItem;
namespace Ui {
class FileManagerSnapShotDialog;
}

class FileManagerSnapShotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerSnapShotDialog(int nMode, QWidget *parent = 0);
    ~FileManagerSnapShotDialog();
    QString strDate() const;

private:
    void addListItem(QString str);
private slots:
    void on_backPushButton_clicked();

//    void on_listWidget_clicked(const QModelIndex &index);

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::FileManagerSnapShotDialog *ui;
    QString m_strDate;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // FILEMANAGERSNAPSHOTDIALOG_H
