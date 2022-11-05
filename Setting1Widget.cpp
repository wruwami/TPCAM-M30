#include "Setting1Widget.h"
#include "ui_Setting1Widget.h"

Setting1Widget::Setting1Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting1Widget)
{
    ui->setupUi(this);
}

Setting1Widget::~Setting1Widget()
{
    delete ui;
}
