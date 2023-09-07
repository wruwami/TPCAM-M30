#include "LocationWidget.h"
#include "ui_LocationWidget.h"

#include <QPainter>

LocationWidget::LocationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationWidget)
{
    ui->setupUi(this);

//    ui->listWidget->row
    //    ui->listWidget->setGeometry(ui->horizontalLayout->geometry());
//    ui->listWidget->setStyleSheet(QString("QListWidget QListView {height : %0;}").arg(ui->listWidget->height()/5));
//    ui->listWidget->addItem("Seoul/Korea");
//    ui->listWidget->addItem("Busan/Korea");

    ui->label->setText("Seoul/Korea");
//    ui->label->setFontSize(23);
    ui->label_2->setText("Busan/Korea");
//    ui->label_2->setFontSize(23);
}

LocationWidget::~LocationWidget()
{
    delete ui;
}

void LocationWidget::paintEvent(QPaintEvent *event)
{
    QPen Pen(Qt::black);
    Pen.setStyle(Qt::DashLine);
    QPainter painter(this);
    painter.setPen(Pen);

    painter.drawLine(0, height()/5, width(), height()/5);
    painter.drawLine(0, height()/5 * 2, width(), height()/5*2);
    painter.drawLine(0, height()/5 * 3, width(), height()/5*3);
    painter.drawLine(0, height()/5 * 4, width(), height()/5*4);
//    painter.drawLine(0, 0, 0, height()/5);
}

