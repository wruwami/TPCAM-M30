#ifndef FILEMANAGERQUESTIONMESSAGEDIALOG_H
#define FILEMANAGERQUESTIONMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class FileManagerQuestionMessageDialog;
}

class FileManagerQuestionMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerQuestionMessageDialog(QWidget *parent = 0);
    ~FileManagerQuestionMessageDialog();

private:
    Ui::FileManagerQuestionMessageDialog *ui;
};

#endif // FILEMANAGERQUESTIONMESSAGEDIALOG_H
