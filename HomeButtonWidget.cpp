#include "HomeButtonWidget.h"
#include "ui_HomeButtonWidget.h"

#include "WidgetSize.h"

HomeButtonWidget::HomeButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeButtonWidget)
{
    ui->setupUi(this);

    m_pHomePushButton = ui->homePushButton;
    ui->homePushButton->setImage("Main_menu", "home_big_n.bmp");
    ui->homePushButton->setFixedSize(ui->homePushButton->height(), ui->homePushButton->height());
}

HomeButtonWidget::~HomeButtonWidget()
{
    delete ui;
}
