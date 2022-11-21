#include "FileManagerSnapShotDialog.h"
#include "ui_FileManagerSnapShotDialog.h"

FileManagerSnapShotDialog::FileManagerSnapShotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerSnapShotDialog)
{
    ui->setupUi(this);
}

FileManagerSnapShotDialog::~FileManagerSnapShotDialog()
{
    delete ui;
}
