#include "WifiSearchWidget.h"
#include "ui_WifiSearchWidget.h"

#include <QDialog>
#include <QListWidgetItem>

#include "StringLoader.h"

WifiSearchWidget::WifiSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WifiSearchWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;
    ui->filterNameLabel->setText(LoadString("IDS_FILTER_NAME"));

    ui->applyPushButton->setText(LoadString("IDS_APPLY"));
    ui->yesPushButton->setText(LoadString("IDS_YES"));
    ui->noPushButton->setText(LoadString("IDS_NO"));

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->lineEdit->SetMode(KeyboardType);

    startTimer(1000);
}

WifiSearchWidget::~WifiSearchWidget()
{
    delete ui;
}

void WifiSearchWidget::on_applyPushButton_clicked()
{
    m_strFilter = ui->lineEdit->GetString();
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
    m_wifiList = m_networkAccessManager.findActiveWirelesses();
    foreach(auto item, m_wifiList)
    {
        if (!item.contains(m_strFilter))
            m_wifiList.removeOne(item);
    }
    if (!m_wifiList.isEmpty())
        ui->listWidget->clear();
    ui->listWidget->addItems(m_wifiList);

}


void WifiSearchWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    m_strSSID = item->text();
//    item
}

