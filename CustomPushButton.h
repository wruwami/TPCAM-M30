#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QToolButton>

class CustomPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomPushButton(QWidget *parent = 0);
    void setImage(QString path_name, QString file_name);
    void setImage(QString path_name, QString file_name, QSize size);
signals:

private:
    QPixmap m_pixmap;
    QSize m_size;
    QIcon m_icon;
    float m_ratio = 0;
public slots:


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // CUSTOMPUSHBUTTON_H
