#include "KeypadDialog.h"
#include "ui_KeypadDialog.h"

#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"

#include "StringLoader.h"

KeypadDialog::KeypadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeypadDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

//    setGeometry();

    QFile file;
    file.setFileName(":/keyboard/keypad.json");    // Using it from the resource file.
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    ui->verticalLayout->addWidget(k);

}

KeypadDialog::~KeypadDialog()
{
    delete ui;
}

void KeypadDialog::onKeyPressed(const QString &iKey, Key *mKey)
{

}

