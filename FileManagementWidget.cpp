#include "FileManagementWidget.h"
#include "ui_FileManagementWidget.h"

FileManagementWidget::FileManagementWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagementWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
}

FileManagementWidget::~FileManagementWidget()
{
    delete ui;
}
