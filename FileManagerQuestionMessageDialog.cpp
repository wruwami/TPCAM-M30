#include "FileManagerQuestionMessageDialog.h"
#include "ui_FileManagerQuestionMessageDialog.h"

FileManagerQuestionMessageDialog::FileManagerQuestionMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerQuestionMessageDialog)
{
    ui->setupUi(this);
}

FileManagerQuestionMessageDialog::~FileManagerQuestionMessageDialog()
{
    delete ui;
}
