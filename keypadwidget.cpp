#include "keypadwidget.h"
#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

//#include "widgetsize.h"
#include "Color.h"

KeypadWidget::KeypadWidget(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setStyleSheet("");
//    this->setWindowIcon()

//    setBackGroundColor(this, Color::KeyPadBackGround);

//    QRect rect = WidgetSize::GetInstance()->GetWidgetSizePos(QRect(471, 391, 399, 485));
//    setGeometry(rect);

    QFile file;
    file.setFileName(":/keyboard/keypad.json");    // Using it from the resource file.

    // = new KeyLayout(&file);
    //Keyboard *k = new Keyboard(*kl, InputMode::Mouse);
    Keyboard *k = new Keyboard(file, InputMode::Keypad, this);
    KeyLayout *kl = k->GetKeyLayout();
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_tEdit = new QLineEdit(this);
    QCursor cursor;
    m_tEdit->setCursor(cursor);
//    m_tEdit->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(471, 391, 264, 60), rect.topLeft()));
    QPushButton *pCloseButton = new QPushButton(this);
    QPixmap pixmap(":/icon/icon/10_close.png");
    pCloseButton->setIcon(pixmap);
    pCloseButton->setIconSize(pixmap.rect().size());
    pCloseButton->setStyleSheet(QString("QPushButton {background-color:rgba(255,255,255,0); border:none;}"));
//    pCloseButton->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(717, 395, 58, 56), rect.topLeft()));


    QHBoxLayout *hlayout = new QHBoxLayout(this);

    hlayout->addWidget(m_tEdit);
    hlayout->addWidget(pCloseButton);
    layout->addLayout(hlayout);
    layout->addWidget(k);
    setLayout(kl->getLayoutAt(0));

    // ui->centralWidget->layout()->addItem(layout);
    // window->show();
    // Key *key = k->findKeyFromString("space", 0);
    // key->setWidth(80);
    // k->repaint();
//    k->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(559, 761, 370, 370), rect.topLeft()));
    k->setFocus();
    k->show();

    connect(pCloseButton, SIGNAL(clicked()), this, SLOT(slotCloseClicked()));
}

KeypadWidget::~KeypadWidget()
{
    delete m_tEdit;
}

void KeypadWidget::onKeyPressed(const QString &iKey, Key* mKey)
{
    if (iKey == "c")
    {
        m_tEdit->clear();
    }
    else if (iKey == "Enter")
    {
        m_str = m_tEdit->text();
        QDialog::accept();
    }
    else if (iKey == "back")
    {
        m_tEdit->backspace();
    }
    else
    {
        m_tEdit->insert(iKey);
    }

}

const QString &KeypadWidget::str() const
{
    return m_str;
}

void KeypadWidget::slotCloseClicked()
{
    QDialog::reject();
}
