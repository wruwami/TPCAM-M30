#ifndef FILEMANAGERFILETRANSFERWIDGET_H
#define FILEMANAGERFILETRANSFERWIDGET_H

#include <QWidget>

namespace Ui {
class FileManagerFileTransferWidget;
}

class FileManagerFileTransferWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerFileTransferWidget(QWidget *parent = 0);
    ~FileManagerFileTransferWidget();

private:
    Ui::FileManagerFileTransferWidget *ui;
};

#endif // FILEMANAGERFILETRANSFERWIDGET_H
