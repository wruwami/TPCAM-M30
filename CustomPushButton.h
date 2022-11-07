#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>

class CustomPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomPushButton(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CUSTOMPUSHBUTTON_H
