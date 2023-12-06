/**
 * @file keyboardwidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief Keyboard 라이브러리를 이용하여 키패드를 구현한 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

class Key;
class KeyboardWidget : public QDialog
{
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = nullptr);
    ~KeyboardWidget();
    void onKeyPressed(const QString &iKey, Key* mKey);
    const QString &str() const;

private:
    QPushButton* m_pCloseButton;
    QLineEdit * m_tEdit;
    QPushButton* m_pSaveButton;
    QPushButton* m_pCancelButton;
    QString m_str;

signals:
private slots:
    void slotCloseButtonClicked();
    void slotSaveButtonClicked();
    void slotCancelButtonClicked();
};

#endif // KEYBOARDWIDGET_H
