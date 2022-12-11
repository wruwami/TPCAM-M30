#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include <QListWidget>

class CustomList : public QListWidget
{
    Q_OBJECT
public:
    explicit CustomList(QWidget *parent = 0);
protected:
    QStyleOptionViewItem viewOptions() const override{
        QStyleOptionViewItem option = QListWidget::viewOptions();
        option.decorationPosition = QStyleOptionViewItem::Left;
        return option;
    }
signals:

public slots:
};

#endif // CUSTOMLIST_H
