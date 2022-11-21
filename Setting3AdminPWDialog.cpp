#include "Setting3AdminPWDialog.h"
#include "ui_Setting3AdminPWDialog.h"

Setting3AdminPWDialog::Setting3AdminPWDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting3AdminPWDialog)
{
    ui->setupUi(this);
}

Setting3AdminPWDialog::~Setting3AdminPWDialog()
{
    delete ui;
}
