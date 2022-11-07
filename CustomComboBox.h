#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>

class CustomComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit CustomComboBox(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CUSTOMCOMBOBOX_H
