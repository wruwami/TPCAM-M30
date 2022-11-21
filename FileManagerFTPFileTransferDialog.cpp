#include "FileManagerFTPFileTransferDialog.h"
#include "ui_FileManagerFTPFileTransferDialog.h"

FileManagerFTPFileTransferDialog::FileManagerFTPFileTransferDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerFTPFileTransferDialog)
{
    ui->setupUi(this);
}

FileManagerFTPFileTransferDialog::~FileManagerFTPFileTransferDialog()
{
    delete ui;
}
