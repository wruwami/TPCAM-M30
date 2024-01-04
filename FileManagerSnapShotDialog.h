/**
 * @file FileManagerSnapShotDialog.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일매니저에서 현재 모드(I,A,V,S,M)에 따라 폴더를 보여주는 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILEMANAGERSNAPSHOTDIALOG_H
#define FILEMANAGERSNAPSHOTDIALOG_H

#include <QDialog>

class CustomPushButton;
class QListWidgetItem;
namespace Ui {
class FileManagerSnapShotDialog;
}

/**
 * @brief 파일매니저에서 현재 모드(I,A,V,S,M)에 따라 폴더를 보여주는 다이얼로그 클래스
 * 
 */
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
    CustomPushButton* m_pBackPushButton = nullptr;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // FILEMANAGERSNAPSHOTDIALOG_H
