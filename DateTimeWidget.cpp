#include "DateTimeWidget.h"
#include "ui_DateTimeWidget.h"

DateTimeWidget::DateTimeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTimeWidget)
{
    ui->setupUi(this);
}

DateTimeWidget::~DateTimeWidget()
{
    delete ui;
}
