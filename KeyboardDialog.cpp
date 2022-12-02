#include "KeyboardDialog.h"
#include "ui_KeyboardDialog.h"

#include <QFile>

#include "StringLoader.h"
#include "WidgetSize.h"

#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"



KeyboardDialog::KeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

//    setGeometry();

    QFile file;
    file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    ui->verticalLayout->addWidget(k);
//    KeyLayout *kl = k->GetKeyLayout();
//    k->setFocus();
//    k->show();


}

KeyboardDialog::~KeyboardDialog()
{
    delete ui;
}

void KeyboardDialog::onKeyPressed(const QString &iKey, Key *mKey)
{

}
