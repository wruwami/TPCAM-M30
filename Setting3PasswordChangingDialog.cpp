#include "Setting3PasswordChangingDialog.h"
#include "ui_Setting3PasswordChangingDialog.h"

Setting3PasswordChangingDialog::Setting3PasswordChangingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting3PasswordChangingDialog)
{
    ui->setupUi(this);
}

Setting3PasswordChangingDialog::~Setting3PasswordChangingDialog()
{
    delete ui;
}
