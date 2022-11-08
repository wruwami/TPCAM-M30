#include "SelfTestWidget.h"
#include "ui_SelfTestWidget.h"

#include "Color.h"

SelfTestWidget::SelfTestWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfTestWidget)
{
    ui->setupUi(this);

    setBackGroundColor(this, 0x000000);
}

SelfTestWidget::~SelfTestWidget()
{
    delete ui;
}
