#include "KeypadDialog.h"
#include "ui_KeypadDialog.h"

#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"

#include "StringLoader.h"
#include "WidgetSize.h"

KeypadDialog::KeypadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeypadDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));
    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

//    setGeometry();

    QFile file;
    file.setFileName(":/keyboard/keypad.json");    // Using it from the resource file.
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    ui->verticalLayout->addWidget(k);

    ui->verticalLayout->setStretch(0, 1);
    ui->verticalLayout->setStretch(1, 1);
    ui->verticalLayout->setStretch(2, 4);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

KeypadDialog::~KeypadDialog()
{
    delete ui;
}

void KeypadDialog::onKeyPressed(const QString &iKey, Key *mKey)
{
    if (iKey == "c")
    {
        ui->lineEdit->clear();
    }
    else if (iKey == "Enter")
    {
        m_str = ui->lineEdit->text();
        QDialog::accept();
    }
    else if (iKey == "back")
    {
        ui->lineEdit->backspace();
    }
    else
    {
        ui->lineEdit->insert(iKey);
    }
}

QString KeypadDialog::str() const
{
    return m_str;
}

void KeypadDialog::on_okPushButton_clicked()
{
    ui->lineEdit->clear();
    QDialog::accept();
}

void KeypadDialog::on_cancelPushButton_clicked()
{
    ui->lineEdit->clear();
    QDialog::reject();
}
