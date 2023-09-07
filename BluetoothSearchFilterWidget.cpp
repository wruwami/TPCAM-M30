#include "BluetoothSearchFilterWidget.h"
#include "ui_BluetoothSearchFilterWidget.h"

#include <QDialog>

#include "StringLoader.h"

BluetoothSearchFilterWidget::BluetoothSearchFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothSearchFilterWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;
    ui->filterNameLabel->setText(LoadString("IDS_FILTER_NAME"));
    ui->filterNameLabel->setFontSize(23);

    ui->applyPushButton->setText(LoadString("IDS_APPLY"));
    ui->applyPushButton->setFontSize(23);
    ui->yesPushButton->setText(LoadString("IDS_YES"));
    ui->yesPushButton->setFontSize(23);
    ui->noPushButton->setText(LoadString("IDS_NO"));
    ui->noPushButton->setFontSize(23);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

BluetoothSearchFilterWidget::~BluetoothSearchFilterWidget()
{
    delete ui;
}

void BluetoothSearchFilterWidget::on_applyPushButton_clicked()
{

}

void BluetoothSearchFilterWidget::on_yesPushButton_clicked()
{
    m_pParent->accept();
}

void BluetoothSearchFilterWidget::on_noPushButton_clicked()
{
    m_pParent->reject();
}
