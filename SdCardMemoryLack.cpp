#include "SdCardMemoryLack.h"
#include "ui_SdCardMemoryLack.h"

#include <QDialog>

#include "StringLoader.h"

SdCardMemoryLack::SdCardMemoryLack(QString msg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SdCardMemoryLack)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;

    ui->warningLabel->setText(LoadString("IDS_CRACK_DOWN_MESSAGE"));
    ui->warningLabel->setFontSize(23);
    ui->warningLabel->setColor(Qt::black);
    ui->warningLabel2->setText(LoadString("IDS_CRACK_DOWN_MESSAGE2"));
    ui->warningLabel2->setFontSize(23);
    ui->warningLabel2->setColor(Qt::black);
    ui->sdCardValueLabel->setText(msg);
    ui->sdCardValueLabel->setFontSize(23);
    ui->sdCardValueLabel->setColor(Qt::red);

    ui->pushButton->setText(LoadString("IDS_OK"));

}

SdCardMemoryLack::~SdCardMemoryLack()
{
    delete ui;
}

void SdCardMemoryLack::on_pushButton_clicked()
{
    m_pParent->accept();
}

