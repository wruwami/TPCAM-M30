/**
 * @file CustomCheckBox.h
 * @author wruwami (wruwami@naver.com)
 * @brief QCheckBox 상속하여 공통으로 사용하는 CheckBox 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
