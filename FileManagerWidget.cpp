#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);

//    QFrame *line = new QFrame;
//    line->setGeometry(QRect(ui->verticalLayout_2->contentsRect()));
//    line->setFrameShape(QFrame::HLine); // Replace by VLine for vertical line
//    line->setFrameShadow(QFrame::Sunken);
//    line->setLineWidth(2);
//    line->setMidLineWidth(1);
//    line->setFrameShape(QFrame::HLine);
//    line->setFrameShadow(QFrame::Raised);

//    ui->verticalLayout_2->addWidget(line);

//    QTableWidgetItem qTableWidgetItem = new QTableWidgetItem;
//    ui->tableWidget->setHorizontalHeaderItem(0, qTableWidgetItem);
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}
