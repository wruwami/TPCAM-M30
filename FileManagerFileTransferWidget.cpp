#include "FileManagerFileTransferWidget.h"
#include "ui_FileManagerFileTransferWidget.h"

#include "StringLoader.h"

#include "FileFormat.h"

FileManagerFileTransferWidget::FileManagerFileTransferWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerFileTransferWidget)
{
    ui->setupUi(this);

    ui->fileCountLabel->setText("4/100");
}

FileManagerFileTransferWidget::~FileManagerFileTransferWidget()
{
    delete ui;
}
