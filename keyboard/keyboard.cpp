#include <QPainter>
#include <QMouseEvent>
#include <QDebug>


#include "keylayout.h"
#include "keyboard.h"
#include "../KeyboardDialog.h"
#include "../KeypadDialog.h"
#include "StringLoader.h"
//#include "../datepickerwidget.h"

Keyboard::Keyboard(QFile &iJsonFile, InputMode iInputMode, QWidget *iParent) : QStackedWidget(iParent)
{
    // currentKey = nullptr;
    // currentindexkeyboard = 0;

    m_parent = iParent;

    _keylayout = new KeyLayout(iJsonFile, this);

    foreach (QGridLayout *mLayout, _keylayout->getLayouts()) {
        QWidget *mWidget = new QWidget(this);
        mWidget->setLayout(mLayout->layout());
        mLayout->setMargin(0);
        this->addWidget(mWidget);
    }

    this->setCurrentIndex(0);
    setFocusPolicy(Qt::StrongFocus);

    this->show();

    switch (iInputMode) {

        case InputMode::Keypad:
        case InputMode::Keypad2:
        case InputMode::keyboard:
        case InputMode::DatePicker:
        case InputMode::Mouse: {
            _inputMode = iInputMode;
            break;
        }
        case InputMode::Mixed:
            throw std::logic_error{"Unimplemented mode"};
        default:
            throw std::logic_error{"Undefined mode, please select a valid mode"};
    }

    Keyboard::connect(_keylayout, SIGNAL(keyPressed(QString, Key*)), this, SLOT(onKeyPressed(QString, Key*)));
}

Keyboard::~Keyboard()
{

}

KeyLayout *Keyboard::GetKeyLayout()
{
    return _keylayout;
}

void Keyboard::onKeyPressed(const QString &iKey, Key* mKey)
{
    QString mLayoutName;
    if (_keylayout->isSwitchKey(iKey, mLayoutName)) {
        this->currentWidget()->hide();
        if (GetLanguage() != "english")
        {
            if (iKey.contains("lower") || iKey.contains("upper")/* == "Lowr" || iKey == "Caps" || iKey == "ABC"*/)
            {
                if (m_nLangauge == English)
                {
                    m_nLangauge = LanguageCode();
                    if (GetLanguage() == "korean")
                    {
                        hangul_ic_reset(m_hic);
                        m_bFirst = true;
                    }
                }
                else
                {
                    if (GetLanguage() == "korean")
                    {
                        hangul_ic_reset(m_hic);
                        m_bFirst = true;
                    }

//                    mLayoutName.insert(0, "en");
                    m_nLangauge = English;
                }

            }
            if (iKey == "Lowr" || iKey == "Caps" || iKey == "ABC")
            {
                if (m_nLangauge == English)
                {
                    mLayoutName.insert(0, "en");
//                    m_nLangauge = LanguageCode();
                }
                else
                {
//                    m_nLangauge = English;
                }

            }
        }
        int idx = _keylayout->getLayoutIndex(mLayoutName);
        setCurrentIndex(idx);

        this->currentWidget()->show();
    }
    else
    {
        if (_inputMode == keyboard)
        {
            ((KeyboardDialog*)m_parent)->onKeyPressed(iKey, mKey);
        }
        else if (_inputMode == Keypad)
        {
            ((KeypadDialog*)m_parent)->onKeyPressed(iKey, mKey);
        }

        //if (m_parent == (KeypadWidget*))
        //m_parent->onKeyPressed(iKey);
        //m_pTextEdit->setText(iKey);
    }
}

void Keyboard::setNLangauge(Langauge newNLangauge)
{
    m_nLangauge = newNLangauge;
}

QString Keyboard::LanguagePrefix()
{
    if (GetLanguage() == "english")
        return "en";
    else if (GetLanguage() == "spanish")
        return "es";
    else if (GetLanguage() == "arabic")
        return "ar";
    else if (GetLanguage() == "french")
        return "fr";
    else if (GetLanguage() == "korean")
        return "ko";
    else if (GetLanguage() == "portuguese")
        return "pt";
}

Langauge Keyboard::LanguageCode()
{
    if (GetLanguage() == "english")
        return English;
    else if (GetLanguage() == "spanish")
        return Spanish;
    else if (GetLanguage() == "arabic")
        return Arabic;
    else if (GetLanguage() == "french")
        return French;
    else if (GetLanguage() == "korean")
        return Korean;
    else if (GetLanguage() == "portuguese")
        return Portuguese;

}

bool Keyboard::bFirst() const
{
    return m_bFirst;
}

void Keyboard::setBFirst(bool newBFirst)
{
    m_bFirst = newBFirst;
}

void Keyboard::setHic(HangulInputContext *newHic)
{
    m_hic = newHic;
}

Langauge Keyboard::nLangauge() const
{
    return m_nLangauge;
}
