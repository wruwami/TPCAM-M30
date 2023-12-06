/**
 * @file CustomList.h
 * @author wruwami (wruwami@naver.com)
 * @brief QListWidget 상속하여 공통으로 사용하는 List 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
