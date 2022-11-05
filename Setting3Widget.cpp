#include "Setting3Widget.h"
#include "ui_Setting3Widget.h"

Setting3Widget::Setting3Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting3Widget)
{
    ui->setupUi(this);
}

Setting3Widget::~Setting3Widget()
{
    delete ui;
}
