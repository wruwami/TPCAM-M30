#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);

//    QTableWidgetItem qTableWidgetItem = new QTableWidgetItem;
//    ui->tableWidget->setHorizontalHeaderItem(0, qTableWidgetItem);
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}
