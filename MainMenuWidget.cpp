#include "MainMenuWidget.h"
#include "ui_MainMenuWidget.h"

#include "Color.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    setBackGroundColor(this, 0x000000);
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}
