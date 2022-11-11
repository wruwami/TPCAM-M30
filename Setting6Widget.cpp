#include "Setting6Widget.h"
#include "ui_Setting6Widget.h"

#include "StringLoader.h"

Setting6Widget::Setting6Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting6Widget)
{
    ui->setupUi(this);

    ui->languageLabel->setText(LoadString("IDS_LANUAGE"));
    ui->bludtoothLabel->setText(LoadString("IDS_BLUETOOTH"));
    ui->FTPLabel->setText(LoadString("IDS_FTP"));
}

Setting6Widget::~Setting6Widget()
{
    delete ui;
}
