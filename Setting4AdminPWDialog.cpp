#include "Setting4AdminPWDialog.h"
#include "ui_Setting4AdminPWDialog.h"

Setting4AdminPWDialog::Setting4AdminPWDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting4AdminPWDialog)
{
    ui->setupUi(this);
}

Setting4AdminPWDialog::~Setting4AdminPWDialog()
{
    delete ui;
}
