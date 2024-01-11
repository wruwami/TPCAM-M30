/**
 * @file WifiSearchWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief Wifi 검색 화면 위젯
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WIFISEARCHWIDGET_H
#define WIFISEARCHWIDGET_H

#include <QWidget>
#include <QEventLoop>

#include "NetworkAccessManager.h"


namespace Ui {
class WifiSearchWidget;
}
class QListWidgetItem;
/**
 * @brief Wifi 검색 화면 위젯 클래스
 * 
 */
class WifiSearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WifiSearchWidget(QWidget *parent = 0);
    ~WifiSearchWidget();

public slots:
    void on_startWifySearch();

private slots:
    void on_applyPushButton_clicked();
    void on_yesPushButton_clicked();
    void on_noPushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_wifiSearchPushButton_clicked();

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
    void sig_sendConnectingState(bool);
};

#endif // WIFISEARCHWIDGET_H
