#include "KeypadDialog.h"
#include "ui_KeypadDialog.h"

KeypadDialog::KeypadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeypadDialog)
{
    ui->setupUi(this);
}

KeypadDialog::~KeypadDialog()
{
    delete ui;
}

void KeypadDialog::onKeyPressed(const QString &iKey, Key *mKey)
{

}

