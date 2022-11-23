#include "EnforcementWarningMessageWidget.h"
#include "ui_EnforcementWarningMessageWidget.h"

#include "StringLoader.h"

EnforcementWarningMessageWidget::EnforcementWarningMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementWarningMessageWidget)
{
    ui->setupUi(this);

    ui->warning1Label->setText(LoadString("IDS_ENFORCEMENT_WARNING1"));
    ui->warning2Label->setText(LoadString("IDS_ENFORCEMENT_WARNING2"));
    ui->sdCardLabel->setText(LoadString("IDS_SD_CARD"));

    ui->pushButton->setText(LoadString("IDS_OK"));
}

EnforcementWarningMessageWidget::~EnforcementWarningMessageWidget()
{
    delete ui;
}
