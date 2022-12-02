#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>

class Key;
namespace Ui {
class KeyboardDialog;
}

class KeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyboardDialog(QWidget *parent = 0);
    ~KeyboardDialog();
    void onKeyPressed(const QString &iKey, Key* mKey);

private:
    Ui::KeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_H
