#include "HomeButtonWidget.h"
#include "ui_HomeButtonWidget.h"

#include "WidgetSize.h"

HomeButtonWidget::HomeButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeButtonWidget)
{
    ui->setupUi(this);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pHomePushButton = ui->homePushButton;
    ui->homePushButton->setImage("Main_menu", "home_big_n.bmp");
    WidgetSize* ws = WidgetSize::GetInstance();
    ui->homePushButton->setFixedSize(ws->GetWidgetWidth(122), ws->GetWidgetHeight(122));
//    ui->homePushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    ui->homePushButton->setFixedSize(ui->homePushButton->height(), ui->homePushButton->height());
}

HomeButtonWidget::~HomeButtonWidget()
{
    delete ui;
}
