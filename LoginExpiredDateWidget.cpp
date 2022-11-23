#include "LoginExpiredDateWidget.h"
#include "ui_LoginExpiredDateWidget.h"

#include "StringLoader.h"

LoginExpiredDateWidget::LoginExpiredDateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginExpiredDateWidget)
{
    ui->setupUi(this);

    ui->label->setText(LoadString("IDS_CALIBRATION_SERVICE_REQUIRED"));
    ui->pushButton->setText(LoadString("IDS_OK"));
}

LoginExpiredDateWidget::~LoginExpiredDateWidget()
{
    delete ui;
}
