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
