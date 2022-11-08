#include "StillImageViewerWidget.h"
#include "ui_StillImageViewerWidget.h"

StillImageViewerWidget::StillImageViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StillImageViewerWidget)
{
    ui->setupUi(this);
}

StillImageViewerWidget::~StillImageViewerWidget()
{
    delete ui;
}
