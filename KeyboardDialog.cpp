#include "KeyboardDialog.h"
#include "ui_KeyboardDialog.h"

#include <QFile>

#include "StringLoader.h"
#include "WidgetSize.h"

#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"

#include "WidgetSize.h"

#ifdef Q_OS_LINUX
    #include "hangul-1.0/hangul.h"
#endif

KeyboardDialog::KeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

    ui->deleteAllPushButton->setImage("Main_menu", "delete_all.bmp");

    QFile file;
    file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    ui->verticalLayout->addWidget(k);
//    KeyLayout *kl = k->GetKeyLayout();
//    k->setFocus();
//    k->show();
    ui->verticalLayout->setStretch(0, 1);
    ui->verticalLayout->setStretch(1, 1);
    ui->verticalLayout->setStretch(2, 4);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

KeyboardDialog::KeyboardDialog(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText(str);
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

    ui->deleteAllPushButton->setImage("Main_menu", "delete_all.bmp");

//    setGeometry();

    QFile file;
    file.setFileName(":/keyboard/kr.json");    // Using it from the resource file.
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    ui->verticalLayout->addWidget(k);
//    KeyLayout *kl = k->GetKeyLayout();
//    k->setFocus();
//    k->show();
    ui->verticalLayout->setStretch(0, 1);
    ui->verticalLayout->setStretch(1, 1);
    ui->verticalLayout->setStretch(2, 4);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

KeyboardDialog::KeyboardDialog(QString str, QString language, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText(str);
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

    ui->deleteAllPushButton->setImage("Main_menu", "delete_all.bmp");

    QFile file;
    file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    ui->verticalLayout->addWidget(k);
//    KeyLayout *kl = k->GetKeyLayout();
//    k->setFocus();
//    k->show();
    ui->verticalLayout->setStretch(0, 1);
    ui->verticalLayout->setStretch(1, 1);
    ui->verticalLayout->setStretch(2, 4);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


KeyboardDialog::~KeyboardDialog()
{
    delete ui;
}

void KeyboardDialog::onKeyPressed(const QString &iKey, Key *mKey)
{
//    QString mLayoutName;

    if (iKey == "space")
    {
        ui->lineEdit->insert(" ");
    }
    else if (iKey == "return")
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

const QString &KeyboardDialog::str() const
{
    return m_str;
}

void KeyboardDialog::on_okPushButton_clicked()
{
    m_str = ui->lineEdit->text();
    ui->lineEdit->clear();
    QDialog::accept();
}

void KeyboardDialog::on_cancelPushButton_clicked()
{
    ui->lineEdit->clear();
    QDialog::reject();
}

void KeyboardDialog::on_deleteAllPushButton_clicked()
{
    ui->lineEdit->clear();
}
