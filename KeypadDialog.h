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

    QString str() const;

private:
    QString m_str;
private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

    void on_deleteAllPushButton_clicked();

private:
    Ui::KeypadDialog *ui;


};

#endif // KEYPADDIALOG_H
