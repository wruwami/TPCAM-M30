#include "Setting4Widget.h"
#include "ui_Setting4Widget.h"

Setting4Widget::Setting4Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting4Widget)
{
    ui->setupUi(this);
}

Setting4Widget::~Setting4Widget()
{
    delete ui;
}
