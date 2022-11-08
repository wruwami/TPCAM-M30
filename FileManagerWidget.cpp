#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}
