#include "SystemInfoWidget.h"
#include "ui_SystemInfoWidget.h"

SystemInfoWidget::SystemInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemInfoWidget)
{
    ui->setupUi(this);
}

SystemInfoWidget::~SystemInfoWidget()
{
    delete ui;
}
