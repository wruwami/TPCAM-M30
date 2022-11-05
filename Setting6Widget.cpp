#include "Setting6Widget.h"
#include "ui_Setting6Widget.h"

Setting6Widget::Setting6Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting6Widget)
{
    ui->setupUi(this);
}

Setting6Widget::~Setting6Widget()
{
    delete ui;
}
