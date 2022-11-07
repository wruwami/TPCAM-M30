#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CUSTOMLABEL_H
