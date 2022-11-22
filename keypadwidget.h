#ifndef KEYPADWIDGET_H
#define KEYPADWIDGET_H

#include <QDialog>
#include <QLineEdit>

class Key;
class KeypadWidget : public QDialog
{
    Q_OBJECT
public:
    explicit KeypadWidget(QWidget *parent = nullptr);
    ~KeypadWidget();
    void onKeyPressed(const QString &iKey, Key* mKey);
    const QString &str() const;

private:
    QLineEdit *m_tEdit;
    QString m_str;
signals:
private slots:
    void slotCloseClicked();
};

#endif // KEYPADWIDGET_H
