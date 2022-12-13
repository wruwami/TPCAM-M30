#include "MovieViewerDialog.h"
#include "ui_MovieViewerDialog.h"

#include "StringLoader.h"

MovieViewerDialog::MovieViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieViewerDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->playPushButton->setText(LoadString("IDS_PLAY"));
    ui->pausePushButton->setText(LoadString("IDS_PAUSE"));
    ui->printPushButton->setText(LoadString("IDS_PRINT"));
}

MovieViewerDialog::~MovieViewerDialog()
{
    delete ui;
}

void MovieViewerDialog::on_quitPushButton_clicked()
{
    accept();
}
