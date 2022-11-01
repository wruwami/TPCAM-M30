#include "LoginWidget.h"
#include "ui_LoginWidget.h"

#include "Color.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0xf2f2f2);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_loginPushButton_clicked()
{

}
