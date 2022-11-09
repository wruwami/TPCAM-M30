#include "DeviceIDWidget.h"
#include "ui_DeviceIDWidget.h"

DeviceIDWidget::DeviceIDWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceIDWidget)
{
    ui->setupUi(this);
}

DeviceIDWidget::~DeviceIDWidget()
{
    delete ui;
}
