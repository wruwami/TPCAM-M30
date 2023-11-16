#include "WifiSearchWidget.h"
#include "ui_WifiSearchWidget.h"

#include <QDialog>
#include <QListWidgetItem>
#include <QThread>

#include "StringLoader.h"

WifiSearchWidget::WifiSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WifiSearchWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;
    ui->filterNameLabel->setText(LoadString("IDS_FILTER_NAME"));
    ui->filterNameLabel->setFontSize(23);

    ui->applyPushButton->setText(LoadString("IDS_WIFI_SEARCH_BUTTON"));
    ui->applyPushButton->setFontSize(23);
    ui->yesPushButton->setText(LoadString("IDS_YES"));
    ui->yesPushButton->setFontSize(23);
    ui->noPushButton->setText(LoadString("IDS_NO"));
    ui->noPushButton->setFontSize(23);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->lineEdit->SetMode(KeyboardType);

//    on_wifiSearchPushButton_clicked();
    startTimer(100);
}

WifiSearchWidget::~WifiSearchWidget()
{
    delete ui;
}

void WifiSearchWidget::on_applyPushButton_clicked()
{
    m_strFilter = ui->lineEdit->GetString();

    emit sig_sendConnectingState(true);
}


void WifiSearchWidget::on_wifiSearchPushButton_clicked()
{

}

void WifiSearchWidget::on_startWifySearch()
{
    m_wifiList = m_networkAccessManager.findActiveWirelesses();
    foreach(auto item, m_wifiList)
    {
        if (!item.contains(m_strFilter))
            m_wifiList.removeOne(item);
    }
    if (!m_wifiList.isEmpty())
        ui->listWidget->clear();
    ui->listWidget->addItems(m_wifiList);

    emit sig_sendConnectingState(false);
}

void WifiSearchWidget::on_yesPushButton_clicked()
{
    emit sig_sendSSID(m_strSSID);
    m_pParent->accept();
}

void WifiSearchWidget::on_noPushButton_clicked()
{
    m_pParent->reject();
}

void WifiSearchWidget::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());

    on_applyPushButton_clicked();
}


void WifiSearchWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    m_strSSID = item->text();
//    item
}
