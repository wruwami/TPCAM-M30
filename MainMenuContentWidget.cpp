#include "MainMenuContentWidget.h"
#include "ui_MainMenuContentWidget.h"

MainMenuContentWidget::MainMenuContentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuContentWidget)
{
    ui->setupUi(this);
}

MainMenuContentWidget::~MainMenuContentWidget()
{
    delete ui;
}
