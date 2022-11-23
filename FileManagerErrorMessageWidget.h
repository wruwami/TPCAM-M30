#ifndef FILEMANAGERERRORMESSAGEWIDGET_H
#define FILEMANAGERERRORMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class FileManagerErrorMessageWidget;
}

class FileManagerErrorMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerErrorMessageWidget(QWidget *parent = 0);
    ~FileManagerErrorMessageWidget();

private:
    Ui::FileManagerErrorMessageWidget *ui;
};

#endif // FILEMANAGERERRORMESSAGEWIDGET_H
