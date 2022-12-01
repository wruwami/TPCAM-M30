#include "HomeButtonWidget.h"
#include "ui_HomeButtonWidget.h"

HomeButtonWidget::HomeButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeButtonWidget)
{
    ui->setupUi(this);

    m_pHomePushButton = ui->homePushButton;
    ui->homePushButton->setImage("Main_menu", "home_big_n.bmp");
}

HomeButtonWidget::~HomeButtonWidget()
{
    delete ui;
}
