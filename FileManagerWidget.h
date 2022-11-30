#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class FileManagerWidget;
}

class FileManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerWidget(QWidget *parent = 0);
    ~FileManagerWidget();

private:
    Ui::FileManagerWidget *ui;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_deletePushButton_clicked();
};

#endif // FILEMANAGERWIDGET_H
