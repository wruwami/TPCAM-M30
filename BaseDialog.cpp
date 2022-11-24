#include "BaseDialog.h"
#include "ui_BaseDialog.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "Color.h"
#include "StringLoader.h"

#include "LoginExpiredDateWidget.h"

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
    case Dialog::LoginExpiredDateWidgetType:
    {
        ui->verticalLayout->addWidget(new LoginExpiredDateWidget);
        ui->titleLabel->setText(LoadString("IDS_LOGIN_EXPIRED_DATE"));
        resize(GetWidgetSize(QSize(1146, 604)));
//        ui->verticalLayout->setStretch();
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

void BaseDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(127,127,127)));
    QRect rect = ui->verticalLayout->itemAt(0)->geometry();
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}
