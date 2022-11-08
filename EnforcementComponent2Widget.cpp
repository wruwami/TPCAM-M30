#include "EnforcementComponent2Widget.h"
#include "ui_EnforcementComponent2Widget.h"

EnforcementComponent2Widget::EnforcementComponent2Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementComponent2Widget)
{
    ui->setupUi(this);
}

EnforcementComponent2Widget::~EnforcementComponent2Widget()
{
    delete ui;
}
