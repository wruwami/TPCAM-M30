#include "IndicatorGPSDialog.h"
#include "ui_IndicatorGpsDialog.h"

IndicatorGpsDialog::IndicatorGpsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicatorGpsDialog)
{
    ui->setupUi(this);
}

IndicatorGpsDialog::~IndicatorGpsDialog()
{
    delete ui;
}
