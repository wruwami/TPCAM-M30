#ifndef FILEMANAGEMENTWIDGET_H
#define FILEMANAGEMENTWIDGET_H

#include <QWidget>

namespace Ui {
class FileManagementWidget;
}

class FileManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagementWidget(QWidget *parent = 0);
    ~FileManagementWidget();

private:
    Ui::FileManagementWidget *ui;
};

#endif // FILEMANAGEMENTWIDGET_H
