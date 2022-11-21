#include "SelfTestWarningMessageDialog.h"
#include "ui_SelfTestWarningMessageDialog.h"

SelfTestWarningMessageDialog::SelfTestWarningMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfTestWarningMessageDialog)
{
    ui->setupUi(this);
}

SelfTestWarningMessageDialog::~SelfTestWarningMessageDialog()
{
    delete ui;
}
