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

private slots:
    void on_pushButton_clicked();

private:
    Ui::FileManagerErrorMessageWidget *ui;
    QDialog* m_pParent;
};

#endif // FILEMANAGERERRORMESSAGEWIDGET_H
