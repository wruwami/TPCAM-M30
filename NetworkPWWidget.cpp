#include "NetworkPWWidget.h"
#include "ui_NetworkPWWidget.h"

NetworkPWWidget::NetworkPWWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkPWWidget)
{
    ui->setupUi(this);
}

NetworkPWWidget::~NetworkPWWidget()
{
    delete ui;
}
