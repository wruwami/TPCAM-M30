#include "FileManagerQuestionMessageWidget.h"
#include "ui_FileManagerQuestionMessageWidget.h"

FileManagerQuestionMessageWidget::FileManagerQuestionMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerQuestionMessageWidget)
{
    ui->setupUi(this);
}

FileManagerQuestionMessageWidget::~FileManagerQuestionMessageWidget()
{
    delete ui;
}
