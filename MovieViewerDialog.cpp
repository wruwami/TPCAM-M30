#include "MovieViewerDialog.h"
#include "ui_MovieViewerDialog.h"

MovieViewerDialog::MovieViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieViewerDialog)
{
    ui->setupUi(this);
}

MovieViewerDialog::~MovieViewerDialog()
{
    delete ui;
}
