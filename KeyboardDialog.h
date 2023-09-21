#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>

#ifdef Q_OS_LINUX
#include "hangul-1.0/hangul.h"
#endif

class Keyboard;
class Key;
namespace Ui {
class KeyboardDialog;
}

class KeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyboardDialog(QString lang, QWidget *parent = 0);
    explicit KeyboardDialog(QString str, QString lang, QWidget *parent = 0);
    ~KeyboardDialog();
    void onKeyPressed(const QString &iKey, Key* mKey);
    const QString &str() const;
private:
    char HangulCovertEnglish(QString str);
#ifdef Q_OS_LINUX
    QString getPreeditString();
    QString getCommitString();
#endif

private:
    QString m_str;
    char m_commit[32] = { '\0', };
    bool m_bFirst = true;
    Keyboard *m_k;
#ifdef Q_OS_LINUX
    HangulInputContext *m_hic = nullptr;
#endif

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

    void on_deleteAllPushButton_clicked();

private:
    Ui::KeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_H
