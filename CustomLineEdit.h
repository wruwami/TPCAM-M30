#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

enum Mode{
    KeyboardType,
    KeypadType,
};

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(QWidget *parent = 0);
    void SetMode(Mode nMode);
    QString GetString();
    QString GetNumber();
    void setFontSize(int);
signals:

public slots:
private:
    Mode m_nMode = KeyboardType;
    QString m_strText;
    QString m_strNum;
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void sig_text(QString);
    void sig_num(QString);
};

#endif // CUSTOMLINEEDIT_H
