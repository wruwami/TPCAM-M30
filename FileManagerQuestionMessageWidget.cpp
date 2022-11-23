#include "FileManagerQuestionMessageWidget.h"
#include "ui_FileManagerQuestionMessageWidget.h"

#include "StringLoader.h"

FileManagerQuestionMessageWidget::FileManagerQuestionMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerQuestionMessageWidget)
{
    ui->setupUi(this);

    ui->questionLabel->setText(LoadString("IDS_DELETE_ALL_QUESTION"));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
}

FileManagerQuestionMessageWidget::~FileManagerQuestionMessageWidget()
{
    delete ui;
}
