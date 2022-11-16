#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QPainter>

class CustomPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomPushButton(QWidget *parent = 0);
    void setImage(QString path_name, QString file_name);
signals:

private:
    QPixmap m_pixmap;
    QIcon m_icon;
public slots:


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // CUSTOMPUSHBUTTON_H
