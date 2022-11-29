#include "BaseDialog.h"
#include "ui_BaseDialog.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "Color.h"
#include "StringLoader.h"

#include "LoginExpiredDateWidget.h"
#include "IndicatorGPSWidget.h"

#include "WidgetSize.h"

BaseDialog::BaseDialog(Dialog dialog, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setBackGroundColor(this, 0xd9d9d9);



    switch (dialog)
    {
    case Dialog::SelfTestWarningMessageWidgetType:
    {

    }
        break;
    case Dialog::LoginExpiredDateWidgetType:
    {
        ui->verticalLayout->addWidget(new LoginExpiredDateWidget);
        ui->titleLabel->setText(LoadString("IDS_LOGIN_EXPIRED_DATE"));
        setSize(1146,604);
    }
    break;
    case Dialog::IndicatorGPSWidgetType:
    {
        ui->verticalLayout->addWidget(new IndicatorGPSWidget);
        ui->titleLabel->setText(LoadString("IDS_LOGIN_EXPIRED_DATE"));
        setSize(1146,604);

    }
        break;
    case Dialog::Setting1LocationWidgetType:
    {

    }
        break;
    case Dialog::Setting3SystemInfoWidgetType:
    {

    }
        break;
    case Dialog::Setting3FactoryDefaultWidgetType:
    {

    }
        break;
    case Dialog::AdminPWWidgetType:
    {

    }
        break;
    case Dialog::PasswordChangingWidgetType:
    {

    }
        break;
    case Dialog::NEtworkPWWidgetType:
    {

    }
        break;
    case Dialog::WifiSearchWidgetType:
    {

    }
        break;
    case Dialog::BluetoothSearchFilterWidgetType:
    {

    }
        break;
    case Dialog::EnforcementWarningMessageWidgetType:
    {

    }
        break;
    case Dialog::FileManagerErrorMessageWidgetType:
    {

    }
        break;
    case Dialog::FileManagerQuestionMessageWidgetType:
    {

    }
        break;
    case Dialog::FileManagerFileTransferWidgetType:
    {

    }
        break;

    default:
    {
    }
        break;
    }

//    if (isClosebutton)


}

BaseDialog::~BaseDialog()
{
    delete ui->verticalLayout->widget();
    delete ui;
}

void BaseDialog::setSize(QSize size)
{
//    ui->verticalLayout->itemAt(0)->widget()->resize(GetWidgetSize(QSize(size.width(), 130)));
//    ui->titleLabel->resize(GetWidgetSize(QSize(size.width(), 130)));
//    ui->verticalLayout->itemAt(1)->widget()->resize(GetWidgetSize(QSize(size.width(), size.height() - 130)));

    resize(GetWidgetSize(size));
    ui->verticalLayout->setStretch(0, 130);
    ui->verticalLayout->setStretch(1, size.height() - 130);
//    ui->titleLabel->resize(GetWidgetSize(QSize(size.width(), 130)));
}

void BaseDialog::setSize(int w, int h)
{
//    ui->verticalLayout->itemAt(0)->widget()->resize(GetWidgetSize(QSize(w, 130)));
//    ui->verticalLayout->itemAt(1)->widget()->resize(GetWidgetSize(QSize(w, h - 130)));
    resize(GetWidgetSize(QSize(w, h)));
    ui->verticalLayout->setStretch(0, 130);
    ui->verticalLayout->setStretch(1, h - 130);
//    ui->titleLabel->resize(GetWidgetSize(QSize(w, 130)));
}



void BaseDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(127,127,127)));
    QRect rect = ui->verticalLayout->itemAt(0)->geometry();
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}
