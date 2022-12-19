#include "PasswordChangingWidget.h"
#include "ui_PasswordChangingWidget.h"

#include <Qdialog>

#include "StringLoader.h"

PasswordChangingWidget::PasswordChangingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordChangingWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;

    ui->currentLabel->setText(LoadString("IDS_CURRENT"));
    ui->newLabel->setText(LoadString("IDS_NEW"));
    ui->confirmLabel->setText(LoadString("IDS_CONFIRM"));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
}

PasswordChangingWidget::~PasswordChangingWidget()
{
    delete ui;
}

void PasswordChangingWidget::on_okPushButton_clicked()
{
    m_pParent->accept();
}

void PasswordChangingWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
