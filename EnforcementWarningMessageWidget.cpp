#include "EnforcementWarningMessageWidget.h"
#include "ui_EnforcementWarningMessageWidget.h"

#include "StringLoader.h"

EnforcementWarningMessageWidget::EnforcementWarningMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementWarningMessageWidget)
{
    ui->setupUi(this);

    ui->warning1Label->setText(LoadString("IDS_ENFORCEMENT_WARNING1"));
    ui->warning1Label->setFontSize(23);
    ui->warning2Label->setText(LoadString("IDS_ENFORCEMENT_WARNING2"));
    ui->warning2Label->setFontSize(23);
    ui->sdCardLabel->setText(LoadString("IDS_SD_CARD"));
    ui->sdCardLabel->setFontSize(23);

    ui->pushButton->setText(LoadString("IDS_OK"));
    ui->pushButton->setFontSize(23);
}

EnforcementWarningMessageWidget::~EnforcementWarningMessageWidget()
{
    delete ui;
}
