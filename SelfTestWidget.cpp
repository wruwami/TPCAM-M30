#include "SelfTestWidget.h"
#include "ui_SelfTestWidget.h"

SelfTestWidget::SelfTestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfTestWidget)
{
    ui->setupUi(this);
}

SelfTestWidget::~SelfTestWidget()
{
    delete ui;
}
