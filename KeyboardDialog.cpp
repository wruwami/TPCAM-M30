#include "KeyboardDialog.h"
#include "ui_KeyboardDialog.h"

#include "regex"

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

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->okPushButton->setFontSize(23);
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));
    ui->cancelPushButton->setFontSize(23);

    ui->deleteAllPushButton->setImage("Main_menu", "delete_all.bmp");

    QFile file;
    if (lang == "english")
    {
        file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    }
    else if (lang == "korean")
    {
        file.setFileName(":/keyboard/ko.json");    // Using it from the resource file.
#ifdef Q_OS_LINUX
        hangul_init();

        m_hic = hangul_ic_new("2");
#endif
    }
    else if (lang == "french")
    {
        file.setFileName(":/keyboard/fr.json");    // Using it from the resource file.

    }
    else if(lang == "spanish")
    {
        file.setFileName(":/keyboard/es.json");    // Using it from the resource file.

    }

    else if (lang == "portuguese")
    {
        file.setFileName(":/keyboard/pt.json");    // Using it from the resource file.

    }
    else if (lang == "arabic")
    {
        file.setFileName(":/keyboard/ar.json");    // Using it from the resource file.

    }

    m_k = new Keyboard(file, InputMode::keyboard, this);
    if (lang == "english")
    {
        m_k->setNLangauge(English);
    }
    else if (lang == "korean")
    {
        m_k->setNLangauge(Korean);
        m_k->setHic(m_hic);
    }
    else if (lang == "french")
    {
        m_k->setNLangauge(French);
    }
    else if(lang == "spanish")
    {
        m_k->setNLangauge(Spanish);
    }

    else if (lang == "portuguese")
    {
        m_k->setNLangauge(Portuguese);
    }
    else if (lang == "arabic")
    {
        m_k->setNLangauge(Arabic);

    }

    ui->verticalLayout->addWidget(m_k);
    ui->verticalLayout->setMargin(9);
//    KeyLayout *kl = k->GetKeyLayout();
//    k->setFocus();
//    k->show();
    ui->verticalLayout->setStretch(0, 1);
    ui->verticalLayout->setStretch(1, 1);
    ui->verticalLayout->setStretch(2, 4);

    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

KeyboardDialog::KeyboardDialog(QString str, QString lang, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText(str);
    setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    setGeometry(GetWidgetSizePos(QRect(0, 125, 1600, 835)));

    ui->okPushButton->setText(LoadString("IDS_OK"));
    ui->cancelPushButton->setText(LoadString("IDS_CANCEL"));

    ui->deleteAllPushButton->setImage("Main_menu", "delete_all.bmp");

    QFile file;
    if (lang == "english")
    {
        file.setFileName(":/keyboard/en.json");    // Using it from the resource file.
    }
    else if (lang == "korean")
    {
        file.setFileName(":/keyboard/ko.json");    // Using it from the resource file.
#ifdef Q_OS_LINUX
        hangul_init();

        m_hic = hangul_ic_new("2");
#endif
    }
    else if (lang == "french")
    {
        file.setFileName(":/keyboard/fr.json");    // Using it from the resource file.

    }
    else if(lang == "spanish")
    {
        file.setFileName(":/keyboard/es.json");    // Using it from the resource file.

    }

    else if (lang == "portuguese")
    {
        file.setFileName(":/keyboard/pt.json");    // Using it from the resource file.

    }
    else if (lang == "arabic")
    {
        file.setFileName(":/keyboard/ar.json");    // Using it from the resource file.

    }

    m_k = new Keyboard(file, InputMode::keyboard, this);
    if (lang == "english")
    {
        m_k->setNLangauge(English);
    }
    else if (lang == "korean")
    {
        m_k->setNLangauge(Korean);
        m_k->setHic(m_hic);
    }
    else if (lang == "french")
    {
        m_k->setNLangauge(French);
    }
    else if(lang == "spanish")
    {
        m_k->setNLangauge(Spanish);
    }

    else if (lang == "portuguese")
    {
        m_k->setNLangauge(Portuguese);
    }
    else if (lang == "arabic")
    {
        m_k->setNLangauge(Arabic);

    }

    ui->verticalLayout->addWidget(m_k);
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
    if (GetLanguage() == "korean")
    {
        hangul_ic_delete(m_hic);

        hangul_fini();
    }
#endif
    delete m_k;

    delete ui;
}

#ifdef Q_OS_LINUX
QString KeyboardDialog::getPreeditString()
{
    const ucschar* str = hangul_ic_get_preedit_string(m_hic);
    return QString::fromUcs4(str);
}

QString KeyboardDialog::getCommitString()
{
    const ucschar* str = hangul_ic_get_commit_string(m_hic);
    return QString::fromUcs4(str);
}
#endif


void KeyboardDialog::onKeyPressed(const QString &iKey, Key *mKey)
{
    char commit[32] = { '\0', };
    char preedit[32] = { '\0', };
    bool bCommit = false;
//    QString mLayoutName;

    if (iKey == "space")
    {
        ui->lineEdit->insert(" ");
    }
    else if (iKey == "&&")
    {
        ui->lineEdit->insert("&");
    }
    else if (iKey == "return")
    {
#ifdef Q_OS_LINUX
        if (m_k->nLangauge() == Korean)
        {
            ui->lineEdit->insert(getPreeditString());
//            1hangul_ic_get_preedit_string();
        }
#endif
        m_str = ui->lineEdit->text();
        QDialog::accept();
    }
    else if (iKey == "back")
    {
        ui->lineEdit->backspace();
        if (GetLanguage() == "korean")
        {
            hangul_ic_reset(m_hic);
            m_k->setBFirst(true);
        }

    }
    else
    {
#ifdef Q_OS_LINUX
        if (m_k->nLangauge() == Korean && IsKoreanChar(iKey))
        {
            int ascii = HangulCovertEnglish(iKey[0]);
            int ret = hangul_ic_process(m_hic, ascii);
            ucs4_to_utf8(commit, hangul_ic_get_commit_string(m_hic), sizeof(commit));

            if (commit[0] != 0) {
                ui->lineEdit->backspace();
//                ui->lineEdit->text();`
                ui->lineEdit->insert(commit);
                bCommit = true;
//                qDebug() << "commit" <<commit;
            }

            if (!bCommit && !m_k->bFirst()){
                ui->lineEdit->backspace();

            }
            m_k->setBFirst(false);
//            if (m_bFirst == true)
//            {
//                m_bFirst = false;
//            }
//            else
//            {
//                ui->lineEdit->backspace();
//            }
            ucs4_to_utf8(preedit, hangul_ic_get_preedit_string(m_hic), sizeof(preedit));

//            preedit = hangul_ic_get_preedit_string(m_hic);
            ui->lineEdit->insert(preedit);
//            qDebug() << "preedit" << preedit;

//            const ucschar preedit;
        }

        else
        {
            ui->lineEdit->insert(iKey);
        }
        //            if (!ret) {
////                char a;
//                QString a;
//                a.sprintf("c", ascii);
////                sprintf(a, "%c", ascii);
//                ui->lineEdit->insert(a);

//            if (ret)
//            {
//                ui->lineEdit->insert(getCommitString());
//            }
//            else
//            {
//                ui->lineEdit->backspace();
//                ui->lineEdit->insert(getCommitString());
//            }


//            QString str = getCommitString();
//            if (!str.isEmpty())
//            {
//                ui->lineEdit->insert(str);
//            }
//            else
//            {
////                ui->lineEdit->backspace();
////                ui->lineEdit->insert(getPreeditString());
//            }
//                ui->lineEdit->installEventFilter()

//            ucs4_to_utf8(m_commit, hangul_ic_get_commit_string(m_hic), sizeof(m_commit));
//            const ucschar* ch = hangul_ic_get_commit_string(m_hic);
//            QString utf8 = QString::fromUcs4(ch);


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
    else if (str == "ㅆ")
        return 'T';
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

bool KeyboardDialog::IsKoreanChar(const QString &str)
{
    QChar ch = str[0].unicode();

    if (ch >= 0x1100 && ch <= 0x11FF)
        return true;

    if (ch >= 0x3130 && ch <= 0x318F)
        return true;

    return false;
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
    if (GetLanguage() == "korean")
    {
        hangul_ic_reset(m_hic);
        m_k->setBFirst(true);
    }

    ui->lineEdit->clear();
}
