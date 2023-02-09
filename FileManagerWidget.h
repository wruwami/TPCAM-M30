#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include <QHeaderView>

#include "FileFormat.h"

namespace Ui {
class FileManagerWidget;
}

class FileManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerWidget(QWidget *parent = 0);
    ~FileManagerWidget();
//public:
//    QWidget* m_pHomePushButton;
private:
    Ui::FileManagerWidget *ui;
    int m_nMode;
    // QWidget interface
    QString m_folder_path;
    QList<AVFileFormat> m_avFileFormatList;
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_deletePushButton_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_searchPushButton_clicked();
    void on_zoomPlayPushButton_clicked();
    void on_sharePushButton_clicked();
    void on_movePushButton_clicked();
    void on_printPushButton_clicked();
    void on_connectPushButton_clicked();
    void on_percentPushButton_clicked();
    void on_ImageVideoComboBox_currentIndexChanged(int index);
    void on_datePushButton_clicked();
};

#endif // FILEMANAGERWIDGET_H
