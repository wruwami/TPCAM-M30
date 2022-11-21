#include "Setting3SystemInfomationDialog.h"
#include "ui_Setting3SystemInfomationDialog.h"

Setting3SystemInfomationDialog::Setting3SystemInfomationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting3SystemInfomationDialog)
{
    ui->setupUi(this);
}

Setting3SystemInfomationDialog::~Setting3SystemInfomationDialog()
{
    delete ui;
}
