#ifndef WIFISEARCHWIDGET_H
#define WIFISEARCHWIDGET_H

#include <QWidget>

#include "NetworkAccessManager.h"


namespace Ui {
class WifiSearchWidget;
}
class QListWidgetItem;
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

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::WifiSearchWidget *ui;
    QDialog* m_pParent;
    NetworkAccessManager m_networkAccessManager;
    QStringList m_wifiList;
    QString m_strFilter;
    QString m_strSSID;
protected:
    void timerEvent(QTimerEvent* event);

signals:
    void sig_sendSSID(QString);
};

#endif // WIFISEARCHWIDGET_H
