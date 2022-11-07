#include "EnforcementCamera.h"
#include "ui_EnforcementCamera.h"

EnforcementCamera::EnforcementCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementCamera)
{
    ui->setupUi(this);
}

EnforcementCamera::~EnforcementCamera()
{
    delete ui;
}
