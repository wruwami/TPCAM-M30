#include "FileManagerErrorMessageWidget.h"
#include "ui_FileManagerErrorMessageWidget.h"

FileManagerErrorMessageWidget::FileManagerErrorMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerErrorMessageWidget)
{
    ui->setupUi(this);
}

FileManagerErrorMessageWidget::~FileManagerErrorMessageWidget()
{
    delete ui;
}
