#include "StillImageViewerDialog.h"
#include "ui_StillImageViewerDialog.h"

StillImageViewerDialog::StillImageViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StillImageViewerDialog)
{
    ui->setupUi(this);
}

StillImageViewerDialog::~StillImageViewerDialog()
{
    delete ui;
}
