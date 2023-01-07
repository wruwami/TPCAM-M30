#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>

#ifdef Q_OS_LINUX
#include "hangul-1.0/hangul.h"
#endif

enum Language{
    English,
    Korean,
    French,
    Spanish,
    Portuguese,
    Arabic,
};

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
    explicit KeyboardDialog(QString str, Language lang, QWidget *parent = 0);
    ~KeyboardDialog();
    void onKeyPressed(const QString &iKey, Key* mKey);
    const QString &str() const;
private:
    int HangulCovertEnglish(QChar ch);
private:
    QString m_str;
    Language m_nLanguage = Language::Korean;
    char m_commit[32] = { '\0', };

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
