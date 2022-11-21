#include "FileManagerErrorMessageDialog.h"
#include "ui_FileManagerErrorMessageDialog.h"

FileManagerErrorMessageDialog::FileManagerErrorMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerErrorMessageDialog)
{
    ui->setupUi(this);
}

FileManagerErrorMessageDialog::~FileManagerErrorMessageDialog()
{
    delete ui;
}
