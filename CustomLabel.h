#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = 0);
//    void setIconImage(QString path_name, QString file_name);
    void setImage(QString path_name, QString file_name);
    void setImage(QString path_name, QString file_name, QSize size);
signals:

public slots:


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // CUSTOMLABEL_H
