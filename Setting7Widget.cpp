#include "Setting7Widget.h"
#include "ui_Setting7Widget.h"

Setting7Widget::Setting7Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting7Widget)
{
    ui->setupUi(this);
}

Setting7Widget::~Setting7Widget()
{
    delete ui;
}
