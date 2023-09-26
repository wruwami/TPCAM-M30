#include "FileManagerQuestionMessageWidget.h"
#include "ui_FileManagerQuestionMessageWidget.h"

#include "BaseDialog.h"
#include "StringLoader.h"

FileManagerQuestionMessageWidget::FileManagerQuestionMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerQuestionMessageWidget)
{
    ui->setupUi(this);

    m_pParent = (QDialog*)parent;
    ui->questionLabel->setText(LoadString("IDS_DELETE_ALL_QUESTION"));
    ui->questionLabel->setFontSize(23);

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->okPushButton->setFontSize(23);
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cancelPushButton->setFontSize(23);
}

FileManagerQuestionMessageWidget::~FileManagerQuestionMessageWidget()
{
    delete ui;
}

void FileManagerQuestionMessageWidget::on_okPushButton_clicked()
{
//    BaseDialog baseDialog(AdminPWWidgetType, Qt::AlignmentFlag::AlignLeft, "");
//    if (baseDialog.exec() == QDialog::Accepted)
    m_pParent->accept();
}

void FileManagerQuestionMessageWidget::on_cancelPushButton_clicked()
{
    m_pParent->reject();
}
