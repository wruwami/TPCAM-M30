#ifndef WIFISEARCHWIDGET_H
#define WIFISEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class WifiSearchWidget;
}

class WifiSearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WifiSearchWidget(QWidget *parent = 0);
    ~WifiSearchWidget();

private slots:
    void on_applyPushButton_clicked();
    void on_yesPushButton_clicked();
    void on_noPushButton_clicked();

private:
    Ui::WifiSearchWidget *ui;
    QDialog* m_pParent;
};

#endif // WIFISEARCHWIDGET_H
