#include "Setting4WifiSearchDialog.h"
#include "ui_Setting4WifiSearchDialog.h"

Setting4WifiSearchDialog::Setting4WifiSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting4WifiSearchDialog)
{
    ui->setupUi(this);
}

Setting4WifiSearchDialog::~Setting4WifiSearchDialog()
{
    delete ui;
}
