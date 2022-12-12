#include "FactoryDefaultWidget.h"
#include "ui_FactoryDefaultWidget.h"

#include <QDialog>

#include "StringLoader.h"

FactoryDefaultWidget::FactoryDefaultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FactoryDefaultWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;
    ui->factoryDefaultLabel->setText(LoadString("IDS_ARE_U_SURE_FACTORY_DEFAULT"));
    ui->pwLabel->setText(LoadString("IDS_PW"));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
}

FactoryDefaultWidget::~FactoryDefaultWidget()
{
    delete ui;
}

void FactoryDefaultWidget::on_okPushButton_clicked()
{
    m_pParent->accept();
}

void FactoryDefaultWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
