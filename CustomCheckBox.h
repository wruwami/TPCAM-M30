#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QCheckBox>

class CustomCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit CustomCheckBox(QWidget *parent = 0);
    void setFontSize(int);

signals:

public slots:

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CUSTOMCHECKBOX_H
