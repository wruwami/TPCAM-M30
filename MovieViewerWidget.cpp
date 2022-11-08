#include "MovieViewerWidget.h"
#include "ui_MovieViewerWidget.h"

MovieViewerWidget::MovieViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovieViewerWidget)
{
    ui->setupUi(this);
}

MovieViewerWidget::~MovieViewerWidget()
{
    delete ui;
}
