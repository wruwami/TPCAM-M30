#include "StillImageViewerDialog.h"
#include "ui_StillImageViewerDialog.h"

#include "StringLoader.h"
#include "WidgetSize.h"

StillImageViewerDialog::StillImageViewerDialog(AVFileFormat avFileFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StillImageViewerDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0,0, 1600, 960)));

    m_file_path = avFileFormat.file_path;
//    ui->imageLabel->setText(LoadString("IDS_STILL_IMAGE_VIEWER"));

    ui->quitPushButton->setText(LoadString("IDS_QUIT"));
    ui->quitPushButton->setFontSize(23);
    ui->originPushButton->setText(LoadString("IDS_ORIGIN"));
    ui->originPushButton->setFontSize(23);
    ui->printPushButton->setText(LoadString("IDS_PRINT"));
    ui->printPushButton->setFontSize(23);
}

StillImageViewerDialog::~StillImageViewerDialog()
{
    delete ui;
}

void StillImageViewerDialog::paintEvent(QPaintEvent *event)
{

}

void StillImageViewerDialog::resizeEvent(QResizeEvent *event)
{
    ui->imageLabel->setImage(m_file_path, ui->imageLabel->size());
}

void StillImageViewerDialog::on_quitPushButton_clicked()
{
    accept();
}

void StillImageViewerDialog::on_plusPushButton_clicked()
{
    if (m_factor == 32)
        return;

    m_factor *= 2;
    ui->imageLabel->setZoom(m_factor, ui->imageLabel->rect());
}

void StillImageViewerDialog::on_minusPushButton_clicked()
{
    m_factor /= 2;
    if (m_factor < 1)
        m_factor = 1;
    ui->imageLabel->setZoom(m_factor, ui->imageLabel->rect());
}

void StillImageViewerDialog::on_originPushButton_clicked()
{
    m_factor = 1;
    ui->imageLabel->setImage(m_file_path, ui->imageLabel->size());
}
