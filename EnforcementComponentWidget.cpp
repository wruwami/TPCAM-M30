#include "EnforcementComponentWidget.h"
#include "ui_EnforcementComponentWidget.h"

EnforcementComponentWidget::EnforcementComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementComponentWidget)
{
    ui->setupUi(this);
}

EnforcementComponentWidget::~EnforcementComponentWidget()
{
    delete ui;
}
