#ifndef CUSTOMZOOMLABEL_H
#define CUSTOMZOOMLABEL_H

#include <QLabel>

class CustomZoomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomZoomLabel(QWidget *parent = 0);
    //    void setIconImage(QString path_name, QString file_name);
    void setImageFromAvi(QString file_path, QSize size);
    void setImage(QString file_path, QSize size);
    void resizeImage(QSize size);
    void setImage(QPixmap pixmap);
    void setImage(QString path_name, QString file_name);
    void setImage(QString path_name, QString file_name, QSize size);
    void removeImage();
private:
    QPixmap scaleImage(double factor);
private:
    QPixmap m_pixmap;
    QPixmap m_fitpixmap;
    bool m_isZoom = false;
signals:

public slots:
        // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // CUSTOMZOOMLABEL_H
