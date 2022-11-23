#ifndef FILEMANAGERQUESTIONMESSAGEWIDGET_H
#define FILEMANAGERQUESTIONMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class FileManagerQuestionMessageWidget;
}

class FileManagerQuestionMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerQuestionMessageWidget(QWidget *parent = 0);
    ~FileManagerQuestionMessageWidget();

private:
    Ui::FileManagerQuestionMessageWidget *ui;
};

#endif // FILEMANAGERQUESTIONMESSAGEWIDGET_H
