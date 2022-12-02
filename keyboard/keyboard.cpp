#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "keylayout.h"
#include "keyboard.h"
#include "../KeyboardDialog.h"
#include "../KeypadDialog.h"
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
