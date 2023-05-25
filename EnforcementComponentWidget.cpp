#include "EnforcementComponentWidget.h"
#include "ui_EnforcementComponentWidget.h"

#include <QPainter>

#include "StringLoader.h"

EnforcementComponentWidget::EnforcementComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementComponentWidget)
{
    ui->setupUi(this);

    ui->hidePushButton->setText(LoadString("IDS_HIDE"));
    ui->readyPushButton->setText(LoadString("IDS_READY"));
    ui->zoomRangePushButton->setText("Z: 100~160 m");
    ui->dzPlusPushButton->setText(LoadString("IDS_DZ_PLUS"));
    ui->dzMinusPushButton->setText(LoadString("IDS_DZ_MINUS"));

    ui->saveImagePushButton->setText(LoadString("IDS_SAVE_IMAGE"));
    ui->truckPushButton->setImage("enforcement", "truck.jpg");
    ui->bikePushButton->setImage("enforcement", "bike.jpg");

    ui->speedLabel->setText("SL: 100km/h\nT80km/h\nM60km/h");
    ui->speedLabel->setDisabled(true);

    QSizePolicy sp_retain = ui->hidePushButton->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->hidePushButton->setSizePolicy(sp_retain);
    ui->readyPushButton->setSizePolicy(sp_retain);
    ui->zoomRangePushButton->setSizePolicy(sp_retain);
    ui->dzPlusPushButton->setSizePolicy(sp_retain);
    ui->dzMinusPushButton->setSizePolicy(sp_retain);

    ui->saveImagePushButton->setSizePolicy(sp_retain);
    ui->truckPushButton->setSizePolicy(sp_retain);
    ui->bikePushButton->setSizePolicy(sp_retain);

    ui->speedLabel->setSizePolicy(sp_retain);

    ui->enforcementCountLabel->setSizePolicy(sp_retain);
    ui->enforcementDistanceSpeedLabel->setSizePolicy(sp_retain);
    ui->enforcementTimeLabel->setSizePolicy(sp_retain);

}

EnforcementComponentWidget::~EnforcementComponentWidget()
{
    delete ui;
}

void EnforcementComponentWidget::on_hidePushButton_clicked()
{
    m_bHide = !m_bHide;
    if (m_bHide)
    {
        ui->hidePushButton->setText(LoadString("IDS_HIDE"));
        hide();
    }
    else
    {
        ui->hidePushButton->setText(LoadString("IDS_SHOW"));
        show();
    }
}

void EnforcementComponentWidget::doShartAction()
{

}

void EnforcementComponentWidget::hide()
{
    m_isSetOutLine = true;
    ui->readyPushButton->hide();
    ui->zoomRangePushButton->hide();
    ui->dzPlusPushButton->hide();
    ui->dzMinusPushButton->hide();

    ui->saveImagePushButton->hide();
    ui->truckPushButton->hide();
    ui->bikePushButton->hide();

    ui->speedLabel->hide();

    ui->enforcementCountLabel->hide();
    ui->enforcementDistanceSpeedLabel->hide();
    ui->enforcementTimeLabel->hide();
}

void EnforcementComponentWidget::show()
{
    m_isSetOutLine = false;
    ui->readyPushButton->show();
    ui->zoomRangePushButton->show();
    ui->dzPlusPushButton->show();
    ui->dzMinusPushButton->show();

    ui->saveImagePushButton->show();
    ui->truckPushButton->show();
    ui->bikePushButton->show();

    ui->speedLabel->show();

    ui->enforcementCountLabel->show();
    ui->enforcementDistanceSpeedLabel->show();
    ui->enforcementTimeLabel->show();
}

void EnforcementComponentWidget::paintEvent(QPaintEvent *event)
{
//    QWidget::paintEvent(event);

    if (m_isSetOutLine)
    {
        QPainter painter(this);
    //    QStyleOptionFrame  option;
    //    option.initFrom(this);
    //    option.rect = ui->verticalLayout_2->geometry();
    //    option.lineWidth = 1;
    //    option.frameShape = QFrame::Box;
    //    style()->drawPrimitive(QStyle::PE_Frame,  &option,  &painter,  this);

    //    QStyleOptionFrame  option2;
    //    option2.initFrom(this);
    //    option2.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_7->geometry().top() + ui->gridLayout_2->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    //    option2.lineWidth = 1;
    //    option2.frameShape = QFrame::HLine;
    //    style()->drawPrimitive(QStyle::PE_Frame,  &option2,  &painter,  this);

    //    QStyleOptionFrame  option3;
    //    option3.initFrom(this);
    //    option3.rect = QRect(ui->horizontalLayout_7->geometry().left(), (ui->horizontalLayout_5->geometry().top() + ui->horizontalLayout_7->geometry().bottom()) / 2, ui->verticalLayout_2->geometry().width(), 1);
    //    option3.lineWidth = 1;
    //    option3.frameShape = QFrame::HLine;
    //    style()->drawPrimitive(QStyle::PE_Frame,  &option3,  &painter,  this);

        int gap = 3;

        QPen Pen(Qt::red);
        Pen.setStyle(Qt::SolidLine);
        Pen.setWidth(10);
        painter.setPen(Pen);
        painter.drawLine(gap, gap, this->geometry().width() - 2 * gap, gap);
        painter.drawLine(gap, gap, gap, this->geometry().height());
        painter.drawLine(this->geometry().width() - gap, gap, this->geometry().width() - 2 * gap, this->geometry().height() - 2 * gap);
        painter.drawLine(gap, this->geometry().height() - 2 * gap, this->geometry().width() - 2 * gap, this->geometry().height() - 2 * gap);
    }
}
