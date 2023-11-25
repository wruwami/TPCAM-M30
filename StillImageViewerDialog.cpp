#include "StillImageViewerDialog.h"
#include "ui_StillImageViewerDialog.h"

#include "StringLoader.h"
#include "WidgetSize.h"
#include "Print.h"
#include "ImageConverter.h"
#include "thermal_printer.h"
#include "ConfigManager.h"

StillImageViewerDialog::StillImageViewerDialog(AVFileFormat avFileFormat, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StillImageViewerDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0,0, 1600, 960)));

    m_file_path = avFileFormat.file_path;
    m_avFileFormat = avFileFormat;
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

void StillImageViewerDialog::on_printPushButton_clicked()
{
    QJsonObject object = ConfigManager("parameter_setting4.json").GetConfig();
    if (object["printer selection"].toInt() == 2)
    {
        QPixmap pixmap;
        pixmap.load(m_avFileFormat.file_path);
        Print print(m_avFileFormat, pixmap.toImage());
    }
    else
    {
        ImageConverter imageConvert(ui->imageLabel->pixmap()->toImage());
        imageConvert.Convert();

        print_wifi_printer();
    }

}

