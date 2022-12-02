#ifndef KEYPADDIALOG_H
#define KEYPADDIALOG_H

#include <QDialog>

class Key;
namespace Ui {
class KeypadDialog;
}

class KeypadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeypadDialog(QWidget *parent = 0);
    ~KeypadDialog();
    void onKeyPressed(const QString &iKey, Key* mKey);

private:
    Ui::KeypadDialog *ui;


};

#endif // KEYPADDIALOG_H
