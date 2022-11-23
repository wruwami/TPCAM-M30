#include "LocationWidget.h"
#include "ui_LocationWidget.h"

LocationWidget::LocationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationWidget)
{
    ui->setupUi(this);
}

LocationWidget::~LocationWidget()
{
    delete ui;
}
