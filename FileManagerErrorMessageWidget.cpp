#include "FileManagerErrorMessageWidget.h"
#include "ui_FileManagerErrorMessageWidget.h"

#include "StringLoader.h"

FileManagerErrorMessageWidget::FileManagerErrorMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerErrorMessageWidget)
{
    ui->setupUi(this);

    ui->printError1Label->setText(LoadString("IDS_PRINT_ERROR1"));
    ui->printError2Label->setText(LoadString("IDS_PRINT_ERROR2"));

    ui->pushButton->setText(LoadString("IDS_OK"));
}

FileManagerErrorMessageWidget::~FileManagerErrorMessageWidget()
{
    delete ui;
}
