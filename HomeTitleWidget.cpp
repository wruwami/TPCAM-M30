#include "HomeTitleWidget.h"
#include "ui_HomeTitleWidget.h"

HomeTitleWidget::HomeTitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeTitleWidget)
{
    ui->setupUi(this);
}

HomeTitleWidget::~HomeTitleWidget()
{
    delete ui;
}
