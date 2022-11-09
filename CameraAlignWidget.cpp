#include "CameraAlignWidget.h"
#include "ui_CameraAlignWidget.h"

CameraAlignWidget::CameraAlignWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAlignWidget)
{
    ui->setupUi(this);
}

CameraAlignWidget::~CameraAlignWidget()
{
    delete ui;
}
