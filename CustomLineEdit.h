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
signals:

public slots:
private:
    Mode m_nMode = KeyboardType;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // CUSTOMLINEEDIT_H
