#include "Setting3FactorDefaultDialog.h"
#include "ui_Setting3FactorDefaultDialog.h"

Setting3FactorDefaultDialog::Setting3FactorDefaultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting3FactorDefaultDialog)
{
    ui->setupUi(this);
}

Setting3FactorDefaultDialog::~Setting3FactorDefaultDialog()
{
    delete ui;
}
