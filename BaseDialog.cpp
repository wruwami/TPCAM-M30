#include "BaseDialog.h"
#include "ui_BaseDialog.h"

BaseDialog::BaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);
}

BaseDialog::~BaseDialog()
{
    delete ui;
}
