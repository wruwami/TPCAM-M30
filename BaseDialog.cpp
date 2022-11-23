#include "BaseDialog.h"
#include "ui_BaseDialog.h"

#include "Color.h"
#include "StringLoader.h"

#include "LoginExpiredDateWidget.h"

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
