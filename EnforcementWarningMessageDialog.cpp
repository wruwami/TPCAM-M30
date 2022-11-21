#include "EnforcementWarningMessageDialog.h"
#include "ui_EnforcementWarningMessageDialog.h"

EnforcementWarningMessageDialog::EnforcementWarningMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnforcementWarningMessageDialog)
{
    ui->setupUi(this);
}

EnforcementWarningMessageDialog::~EnforcementWarningMessageDialog()
{
    delete ui;
}
