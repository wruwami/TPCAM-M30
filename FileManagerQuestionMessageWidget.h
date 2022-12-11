#ifndef FILEMANAGERQUESTIONMESSAGEWIDGET_H
#define FILEMANAGERQUESTIONMESSAGEWIDGET_H

#include <QWidget>

class QDialog;
namespace Ui {
class FileManagerQuestionMessageWidget;
}

class FileManagerQuestionMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerQuestionMessageWidget(QWidget *parent = 0);
    ~FileManagerQuestionMessageWidget();

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::FileManagerQuestionMessageWidget *ui;
    QDialog* m_pParent;
};

#endif // FILEMANAGERQUESTIONMESSAGEWIDGET_H
