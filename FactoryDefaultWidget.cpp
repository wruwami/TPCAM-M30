#include "FactoryDefaultWidget.h"
#include "ui_FactoryDefaultWidget.h"

FactoryDefaultWidget::FactoryDefaultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FactoryDefaultWidget)
{
    ui->setupUi(this);
}

FactoryDefaultWidget::~FactoryDefaultWidget()
{
    delete ui;
}
