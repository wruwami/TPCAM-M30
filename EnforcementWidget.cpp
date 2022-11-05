#include "EnforcementWidget.h"
#include "ui_EnforcementWidget.h"

EnforcementWidget::EnforcementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementWidget)
{
    ui->setupUi(this);
}

EnforcementWidget::~EnforcementWidget()
{
    delete ui;
}
