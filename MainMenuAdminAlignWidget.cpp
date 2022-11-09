#include "MainMenuAdminAlignWidget.h"
#include "ui_MainMenuAdminAlignWidget.h"

MainMenuAdminAlignWidget::MainMenuAdminAlignWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuAdminAlignWidget)
{
    ui->setupUi(this);
}

MainMenuAdminAlignWidget::~MainMenuAdminAlignWidget()
{
    delete ui;
}
