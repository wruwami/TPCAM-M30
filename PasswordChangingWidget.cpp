#include "PasswordChangingWidget.h"
#include "ui_PasswordChangingWidget.h"

PasswordChangingWidget::PasswordChangingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordChangingWidget)
{
    ui->setupUi(this);
}

PasswordChangingWidget::~PasswordChangingWidget()
{
    delete ui;
}
