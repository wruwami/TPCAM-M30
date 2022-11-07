#include "EnforcementSpeedReady.h"
#include "ui_EnforcementSpeedReady.h"

EnforcementSpeedReady::EnforcementSpeedReady(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementSpeedReady)
{
    ui->setupUi(this);
}

EnforcementSpeedReady::~EnforcementSpeedReady()
{
    delete ui;
}
