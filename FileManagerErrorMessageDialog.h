#ifndef FILEMANAGERERRORMESSAGEDIALOG_H
#define FILEMANAGERERRORMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class FileManagerErrorMessageDialog;
}

class FileManagerErrorMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerErrorMessageDialog(QWidget *parent = 0);
    ~FileManagerErrorMessageDialog();

private:
    Ui::FileManagerErrorMessageDialog *ui;
};

#endif // FILEMANAGERERRORMESSAGEDIALOG_H
