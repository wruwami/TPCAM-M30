#include "Setting5Widget.h"
#include "ui_Setting5Widget.h"

Setting5Widget::Setting5Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting5Widget)
{
    ui->setupUi(this);
}

Setting5Widget::~Setting5Widget()
{
    delete ui;
}
