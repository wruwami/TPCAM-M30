#ifndef CUSTOMIMAGEWIDGET_H
#define CUSTOMIMAGEWIDGET_H

#include <QWidget>

class CustomImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomImageWidget(QWidget *parent = 0);
    void setImage(QString path_name, QString file_name);
signals:
private:
    QPixmap m_pixmap;
public slots:
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // CUSTOMIMAGEWIDGET_H
