#include "AdminPWDialog.h"
#include "ui_AdminPWDialog.h"

AdminPWDialog::AdminPWDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPWDialog)
{
    ui->setupUi(this);
}

AdminPWDialog::~AdminPWDialog()
{
    delete ui;
}
