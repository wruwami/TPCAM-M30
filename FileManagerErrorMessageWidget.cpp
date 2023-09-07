#include "FileManagerErrorMessageWidget.h"
#include "ui_FileManagerErrorMessageWidget.h"

#include <QDialog>

#include "StringLoader.h"

FileManagerErrorMessageWidget::FileManagerErrorMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerErrorMessageWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;

    ui->printError1Label->setText(LoadString("IDS_PRINT_ERROR1"));
    ui->printError1Label->setFontSize(23);
    ui->printError2Label->setText(LoadString("IDS_PRINT_ERROR2"));
    ui->printError2Label->setFontSize(23);

    ui->pushButton->setText(LoadString("IDS_OK"));
    ui->pushButton->setFontSize(23);
}

FileManagerErrorMessageWidget::~FileManagerErrorMessageWidget()
{
    delete ui;
}

void FileManagerErrorMessageWidget::on_pushButton_clicked()
{
    m_pParent->accept();
}
