#include "FileManagerFileTransferWidget.h"
#include "ui_FileManagerFileTransferWidget.h"

FileManagerFileTransferWidget::FileManagerFileTransferWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerFileTransferWidget)
{
    ui->setupUi(this);
}

FileManagerFileTransferWidget::~FileManagerFileTransferWidget()
{
    delete ui;
}
