#ifndef CUSTOMSCROLLBAR_H
#define CUSTOMSCROLLBAR_H

#include <QScrollBar>

class CustomScrollbar : public QScrollBar
{
    Q_OBJECT
public:
    explicit CustomScrollbar(int width = 0, QWidget *parent = 0);

signals:

public slots:
};

#endif // CUSTOMSCROLLBAR_H
