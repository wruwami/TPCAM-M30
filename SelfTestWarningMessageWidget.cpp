#include "SelfTestWarningMessageWidget.h"
#include "ui_SelfTestWarningMessageWidget.h"

SelfTestWarningMessageWidget::SelfTestWarningMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfTestWarningMessageWidget)
{
    ui->setupUi(this);
}

SelfTestWarningMessageWidget::~SelfTestWarningMessageWidget()
{
    delete ui;
}
