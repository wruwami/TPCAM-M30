#include "KeyboardDialog.h"
#include "ui_KeyboardDialog.h"

#include <QFile>

#include "StringLoader.h"
#include "WidgetSize.h"

#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"

#include "WidgetSize.h"

#ifdef Q_OS_LINUX
    #include <iconv.h>

#ifdef WORDS_BIGENDIAN
#define UCS4 "UCS-4BE"
#else
#define UCS4 "UCS-4LE"
#endif

#ifndef ICONV_CONST
#define ICONV_CONST
#endif



void ucs4_to_utf8(char *buf, const ucschar *ucs4, size_t bufsize){
    size_t n;
    ICONV_CONST char*  inbuf;
    size_t inbytesleft;
    char*  outbuf;
    size_t outbytesleft;
    size_t ret;
    iconv_t cd;

    for (n = 0; ucs4[n] != 0; n++)
    continue;

    if (n == 0) {
    buf[0] = '\0';
    return;
    }

    cd = iconv_open("UTF-8", UCS4);
    if (cd == (iconv_t)(-1))
    return;

    inbuf = (char*)ucs4;
    inbytesleft = n * 4;
    outbuf = buf;
    outbytesleft = bufsize;
    ret = iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
    (void)ret;

    iconv_close(cd);

    if (outbytesleft > 0)
    *outbuf = '\0';
    else
    buf[bufsize - 1] = '\0';
}
#endif

KeyboardDialog::KeyboardDialog(QString lang, QWidget *parent) :
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
    if (lang == "English")
    {
        file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    }
    else if (lang == "Korean")
    {
        file.setFileName(":/keyboard/ko.json");    // Using it from the resource file.
#ifdef Q_OS_LINUX
        hangul_init();

        m_hic = hangul_ic_new("2");
#endif
    }
    else if (lang == "French")
    {
        file.setFileName(":/keyboard/fr.json");    // Using it from the resource file.

    }
    else if(lang == "Spanish")
    {
        file.setFileName(":/keyboard/es.json");    // Using it from the resource file.

    }

    else if (lang == "Portuguese")
    {
        file.setFileName(":/keyboard/pt.json");    // Using it from the resource file.

    }
    else if (lang == "Arabic")
    {
        file.setFileName(":/keyboard/ar.json");    // Using it from the resource file.

    }


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

//KeyboardDialog::KeyboardDialog(QString str, QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::KeyboardDialog)
//{
//    ui->setupUi(this);

//    ui->lineEdit->setText(str);
//    setWindowFlags(Qt::FramelessWindowHint);
//    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

//    ui->okPushButton->setText(LoadString("IDS_OK"));
//    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

//    ui->deleteAllPushButton->setImage("Main_menu", "delete_all.bmp");

////    setGeometry();

//    QFile file;
//    file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
//#ifdef Q_OS_LINUX
//        hangul_init();

//        m_hic = hangul_ic_new("2");
//#endif
//    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
//    ui->verticalLayout->addWidget(k);
////    KeyLayout *kl = k->GetKeyLayout();
////    k->setFocus();
////    k->show();
//    ui->verticalLayout->setStretch(0, 1);
//    ui->verticalLayout->setStretch(1, 1);
//    ui->verticalLayout->setStretch(2, 4);

//    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//}

KeyboardDialog::KeyboardDialog(QString str, QString lang, QWidget *parent) :
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
    if (lang == "English")
    {
        file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    }
    else if (lang == "Korean")
    {
        file.setFileName(":/keyboard/ko.json");    // Using it from the resource file.
#ifdef Q_OS_LINUX
        hangul_init();

        m_hic = hangul_ic_new("2");
#endif
    }
    else if (lang == "French")
    {
        file.setFileName(":/keyboard/fr.json");    // Using it from the resource file.

    }
    else if(lang == "Spanish")
    {
        file.setFileName(":/keyboard/es.json");    // Using it from the resource file.

    }

    else if (lang == "Portuguese")
    {
        file.setFileName(":/keyboard/pt.json");    // Using it from the resource file.

    }
    else if (lang == "Arabic")
    {
        file.setFileName(":/keyboard/ar.json");    // Using it from the resource file.

    }

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
#ifdef Q_OS_LINUX
    if (m_nLanguage == Korean)
    {
        hangul_ic_delete(m_hic);

        hangul_fini();
    }
#endif

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
#ifdef Q_OS_LINUX
        if (m_nLanguage == Korean)
        {
            int ascii = HangulCovertEnglish(iKey[0]);
            int ret = hangul_ic_process(m_hic, ascii);
            ucs4_to_utf8(m_commit, hangul_ic_get_commit_string(m_hic), sizeof(m_commit));
//            const ucschar* ch = hangul_ic_get_commit_string(m_hic);
//            QString utf8 = QString::fromUcs4(ch);
            ui->lineEdit->insert(m_commit);
        }
        else
        {
            ui->lineEdit->insert(iKey);
        }
#else
        ui->lineEdit->insert(iKey);
#endif

    }
}

const QString &KeyboardDialog::str() const
{
    return m_str;
}

char KeyboardDialog::HangulCovertEnglish(QString str)
{
    if (str == "ㅂ")
        return 'q';
    else if (str == "ㅈ")
        return 'w';
    else if (str == "ㄷ")
        return 'e';
    else if (str == "ㄱ")
        return 'r';
    else if (str == "ㅃ")
        return 'Q';
    else if (str == "ㅉ")
        return 'W';
    else if (str == "ㄸ")
        return 'E';
    else if (str == "ㄲ")
        return 'R';
    else if (str == "ㅁ")
        return 'a';
    else if (str == "ㄴ")
        return 's';
    else if (str == "ㅇ")
        return 'd';
    else if (str == "ㄹ")
        return 'f';
    else if (str == "ㅋ")
        return 'z';
    else if (str == "ㅌ")
        return 'x';
    else if (str == "ㅊ")
        return 'c';
    else if (str == "ㅍ")
        return 'v';
    else if (str == "ㅎ")
        return 'g';
    else if (str == "ㅅ")
        return 't';
    else if (str == "ㅛ")
        return 'y';
    else if (str == "ㅕ")
        return 'u';
    else if (str == "ㅑ")
        return 'i';
    else if (str == "ㅐ")
        return 'o';
    else if (str == "ㅔ")
        return 'p';
    else if (str == "ㅒ")
        return 'O';
    else if (str == "ㅖ")
        return 'P';
    else if (str == "ㅗ")
        return 'h';
    else if (str == "ㅓ")
        return 'j';
    else if (str == "ㅏ")
        return 'k';
    else if (str == "ㅣ")
        return 'l';
    else if (str == "ㅠ")
        return 'b';
    else if (str == "ㅜ")
        return 'n';
    else if (str == "ㅡ")
        return 'm';

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
