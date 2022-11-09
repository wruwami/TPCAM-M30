#include "CameraZoomFocusWidget.h"
#include "ui_CameraZoomFocusWidget.h"

CameraZoomFocusWidget::CameraZoomFocusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraZoomFocusWidget)
{
    ui->setupUi(this);
}

CameraZoomFocusWidget::~CameraZoomFocusWidget()
{
    delete ui;
}
