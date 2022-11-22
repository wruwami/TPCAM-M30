#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"

#include <QDebug>
#include <QPainter>

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);

//    ui->gridLayout_4->setMargin(0);
//    ui->gridLayout_4->setSpacing(0);

//    QFrame* boxFrame = new QFrame;
//    boxFrame->setFrameShape(QFrame::Box);
//    boxFrame->setFrameShadow(QFrame::Plain);
//    boxFrame->setGeometry(ui->gridLayout_3->contentsRect());

//    qDebug() << ui->gridLayout_3->geometry();
//    ui->gridLayout->addWidget(leftFrame, 0, 0, 1, 4);
//    ui->leftFrame->setsi

//    ui->rightFrame->setFrameShape(QFrame::VLine);
//    ui->rightFrame->setFrameShadow(QFrame::Plain);

//    QFrame* upper1Frame = new QFrame(this);
//    upper1Frame->setFrameShape(QFrame::HLine);
//    upper1Frame->setFrameShadow(QFrame::Plain);
//    ui->gridLayout->addWidget(leftFrame, 0, 0, 4, 1);

//    ui->upper2Frame->setFrameShape(QFrame::HLine);
//    ui->upper2Frame->setFrameShadow(QFrame::Plain);

//    ui->upper3Frame->setFrameShape(QFrame::HLine);
//    ui->upper3Frame->setFrameShadow(QFrame::Plain);

//    ui->upper4Frame->setFrameShape(QFrame::HLine);
//    ui->upper4Frame->setFrameShadow(QFrame::Plain);


//    ui->verticalLayout_2->layout()->
//    QFrame *line = new QFrame;
//    line->setGeometry(QRect(ui->verticalLayout_2->contentsRect()));
//    line->setFrameShape(QFrame::Box); // Replace by VLine for vertical line
//    line->setFrameShadow(QFrame::Plain);


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

void FileManagerWidget::resizeEvent(QResizeEvent *event)
{

}

void FileManagerWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QStyleOptionFrame  option;
    option.initFrom(this);
    option.rect = ui->verticalLayout_2->geometry();
    option.lineWidth = 1;
    option.frameShape = QFrame::Box;
    style()->drawPrimitive(QStyle::PE_Frame,  &option,  &painter,  this);

    QStyleOptionFrame  option2;
    option2.initFrom(this);
    option2.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_7->geometry().top() + ui->gridLayout_2->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    option2.lineWidth = 1;
    option2.frameShape = QFrame::HLine;
    style()->drawPrimitive(QStyle::PE_Frame,  &option2,  &painter,  this);

    QStyleOptionFrame  option3;
    option3.initFrom(this);
    option3.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_5->geometry().top() + ui->horizontalLayout_7->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    option3.lineWidth = 1;
    option3.frameShape = QFrame::HLine;
    style()->drawPrimitive(QStyle::PE_Frame,  &option3,  &painter,  this);


}
