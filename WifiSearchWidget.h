#ifndef WIFISEARCHWIDGET_H
#define WIFISEARCHWIDGET_H

#include <QWidget>

#include "NetworkAccessManager.h"

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
    NetworkAccessManager m_networkAccessManager;
    QStringList m_wifiList;
    QString m_strFilter;
protected:
    void timerEvent(QTimerEvent* event);
};

#endif // WIFISEARCHWIDGET_H
