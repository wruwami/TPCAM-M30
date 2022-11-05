#include "FileManagementWidget.h"
#include "ui_FileManagementWidget.h"

FileManagementWidget::FileManagementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagementWidget)
{
    ui->setupUi(this);
}

FileManagementWidget::~FileManagementWidget()
{
    delete ui;
}
