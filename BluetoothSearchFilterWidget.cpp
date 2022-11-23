#include "BluetoothSearchFilterWidget.h"
#include "ui_BluetoothSearchFilterWidget.h"

BluetoothSearchFilterWidget::BluetoothSearchFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothSearchFilterWidget)
{
    ui->setupUi(this);
}

BluetoothSearchFilterWidget::~BluetoothSearchFilterWidget()
{
    delete ui;
}
