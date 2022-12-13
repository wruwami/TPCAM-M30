#include "WifiSearchWidget.h"
#include "ui_WifiSearchWidget.h"

#include <QDialog>

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
}

WifiSearchWidget::~WifiSearchWidget()
{
    delete ui;
}

void WifiSearchWidget::on_applyPushButton_clicked()
{

}

void WifiSearchWidget::on_yesPushButton_clicked()
{
    m_pParent->accept();
}

void WifiSearchWidget::on_noPushButton_clicked()
{
    m_pParent->reject();
}


