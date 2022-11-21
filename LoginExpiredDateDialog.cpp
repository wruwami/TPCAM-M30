#include "LoginExpiredDateDialog.h"
#include "ui_LoginExpiredDateDialog.h"

LoginExpiredDateDialog::LoginExpiredDateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginExpiredDateDialog)
{
    ui->setupUi(this);
}

LoginExpiredDateDialog::~LoginExpiredDateDialog()
{
    delete ui;
}
