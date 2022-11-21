#include "Setting6BluetoothSearchFilterDialog.h"
#include "ui_Setting6BluetoothSearchFilterDialog.h"

Setting6BluetoothSearchFilterDialog::Setting6BluetoothSearchFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting6BluetoothSearchFilterDialog)
{
    ui->setupUi(this);
}

Setting6BluetoothSearchFilterDialog::~Setting6BluetoothSearchFilterDialog()
{
    delete ui;
}
