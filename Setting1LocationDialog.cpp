#include "Setting1LocationDialog.h"
#include "ui_Setting1LocationDialog.h"

Setting1LocationDialog::Setting1LocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting1LocationDialog)
{
    ui->setupUi(this);
}

Setting1LocationDialog::~Setting1LocationDialog()
{
    delete ui;
}
