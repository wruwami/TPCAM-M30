#include "AdminPWWidget.h"
#include "ui_AdminPWWidget.h"

AdminPWWidget::AdminPWWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPWWidget)
{
    ui->setupUi(this);
}

AdminPWWidget::~AdminPWWidget()
{
    delete ui;
}
