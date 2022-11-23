#include "WifiSearchWidget.h"
#include "ui_WifiSearchWidget.h"

WifiSearchWidget::WifiSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WifiSearchWidget)
{
    ui->setupUi(this);
}

WifiSearchWidget::~WifiSearchWidget()
{
    delete ui;
}
