/**
 * @file KeyboardDialog.h
 * @author wruwami (wruwami@naver.com)
 * @brief Keyboard를 이용하여 키보드를 구현한 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
    bool IsKoreanChar(const QString&);
#ifdef Q_OS_LINUX
    QString getPreeditString();
    QString getCommitString();
#endif

private:
    QString m_str;
    char m_commit[32] = { '\0', };
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
