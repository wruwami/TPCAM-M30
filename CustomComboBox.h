/**
 * @file CustomComboBox.h
 * @author wruwami (wruwami@naver.com)
 * @brief QComboBox 상속하여 공통으로 사용하는 ComboBox 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>

class CustomComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit CustomComboBox(QWidget *parent = 0);
//    void setText(QString text);
    void setFontSize(int);
private:
    QSize m_size;
protected:
    void showPopup() override;
signals:

public slots:

public:
    bool eventFilter(QObject *o, QEvent *e) override;
    // QWidget interface
protected:

    void resizeEvent(QResizeEvent *event) override;
};

#endif // CUSTOMCOMBOBOX_H
