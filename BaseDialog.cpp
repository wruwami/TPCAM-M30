#include "BaseDialog.h"
#include "ui_BaseDialog.h"

#include "Color.h"

BaseDialog::BaseDialog(QWidget *parent, bool isCloseButton) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setBackGroundColor(this, 0xd9d9d9);

//    if (isClosebutton)


}

BaseDialog::~BaseDialog()
{
    delete ui;
}
