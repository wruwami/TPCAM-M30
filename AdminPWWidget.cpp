#include "AdminPWWidget.h"
#include "ui_AdminPWWidget.h"

#include "StringLoader.h"

#include <QDialog>

AdminPWWidget::AdminPWWidget(QString meg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPWWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;

    ui->PWLabel->setText(LoadString("IDS_PW"));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
}

AdminPWWidget::~AdminPWWidget()
{
    delete ui;
}

void AdminPWWidget::on_okPushButton_clicked()
{
    m_pParent->accept();
}

void AdminPWWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
