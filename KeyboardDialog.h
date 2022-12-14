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
    explicit KeyboardDialog(QString str, QWidget *parent = 0);
    ~KeyboardDialog();
    void onKeyPressed(const QString &iKey, Key* mKey);
    const QString &str() const;

private:
    QString m_str;
private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::KeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_H
