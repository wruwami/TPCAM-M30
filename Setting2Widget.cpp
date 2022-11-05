#include "Setting2Widget.h"
#include "ui_Setting2Widget.h"

Setting2Widget::Setting2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting2Widget)
{
    ui->setupUi(this);
}

Setting2Widget::~Setting2Widget()
{
    delete ui;
}
