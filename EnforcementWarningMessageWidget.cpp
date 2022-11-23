#include "EnforcementWarningMessageWidget.h"
#include "ui_EnforcementWarningMessageWidget.h"

EnforcementWarningMessageWidget::EnforcementWarningMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementWarningMessageWidget)
{
    ui->setupUi(this);
}

EnforcementWarningMessageWidget::~EnforcementWarningMessageWidget()
{
    delete ui;
}
