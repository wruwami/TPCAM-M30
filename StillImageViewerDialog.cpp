#include "StillImageViewerDialog.h"
#include "ui_StillImageViewerDialog.h"

#include "StringLoader.h"

StillImageViewerDialog::StillImageViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StillImageViewerDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->imageLabel->setText(LoadString("IDS_STILL_IMAGE_VIEWER"));
    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->originPushButton->setText(LoadString("IDS_ORIGIN"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));
}

StillImageViewerDialog::~StillImageViewerDialog()
{
    delete ui;
}

void StillImageViewerDialog::on_quitPushButton_clicked()
{
    accept();
}
