#include "keyboardwidget.h"
#include "keyboard/keyboard.h"
#include "keyboard/keylayout.h"
//#include <QVBoxLayout>
#include <QLineEdit>

#include "StringLoader.h"
#include "Color.h"

KeyboardWidget::KeyboardWidget(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setStyleSheet("");

//    setBackGroundColor(this, Color::KeyboardBackGround);

    QFile file;
    file.setFileName(":/keyboard/en.json");    // Using it from the resource file.

//    QRect rect = WidgetSize::GetInstance()->GetWidgetSizePos(QRect(73, 288, 916, 440));
//    setGeometry(rect);

    // = new KeyLayout(&file);
    //Keyboard *k = new Keyboard(*kl, InputMode::Mouse);
    Keyboard *k = new Keyboard(file, InputMode::keyboard, this);
    KeyLayout *kl = k->GetKeyLayout();
    m_tEdit = new QLineEdit(this);
//    m_tEdit->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(96, 344, 642, 54), rect.topLeft()));
    m_pSaveButton = new QPushButton(this);
    m_pSaveButton->setText(LoadString("IDS_SAVE"));
//    m_pSaveButton->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(758, 344, 92, 54), rect.topLeft()));
    m_pSaveButton->setStyleSheet("QPushButton {color:white;background-color : #7a7a7a;border-radius:10px;}");
    m_pCancelButton = new QPushButton(this);
//    m_pCancelButton->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(868, 344, 92, 54), rect.topLeft()));
    m_pCancelButton->setText(LoadString("IDS_CANCEL"));
    m_pCancelButton->setStyleSheet("QPushButton {color:white;background-color : #7a7a7a;border-radius:10px;}");

    m_pCloseButton = new QPushButton(this);
    QPixmap pixmap(":/icon/icon/10_close.png");
    m_pCloseButton->setIcon(pixmap);
    m_pCloseButton->setIconSize(pixmap.rect().size());
//    m_pCloseButton->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(940, 294, 42, 42), rect.topLeft()));

//    k->setGeometry(WidgetSize::GetInstance()->GetWidgetSizePos(QRect(96, 423, 867, 293), rect.topLeft()));
    k->setFocus();
    k->show();

    connect(m_pCloseButton, SIGNAL(clicked()), this, SLOT(slotCloseButtonClicked()));
    connect(m_pSaveButton, SIGNAL(clicked()), this, SLOT(slotSaveButtonClicked()));
    connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
}

KeyboardWidget::~KeyboardWidget()
{
    delete  m_tEdit;
    delete m_pCloseButton;

    delete m_pSaveButton;
    delete m_pCancelButton;
}

void KeyboardWidget::onKeyPressed(const QString &iKey, Key* mKey)
{
    QString mLayoutName;

    if (iKey == "space")
    {
        m_tEdit->insert(" ");
    }
    else if (iKey == "return")
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


    //    if (_keylayout->isSwitchKey(iKey, mLayoutName)) {
    //        this->currentWidget()->hide();
    //        int idx = _keylayout->getLayoutIndex(mLayoutName);
    //        setCurrentIndex(idx);

    //        this->currentWidget()->show();
    //    }
    //    else
    //    {
    //        m_parent->onKeyPressed(iKey);
    //        //m_pTextEdit->setText(iKey);
    //    }
}

const QString &KeyboardWidget::str() const
{
    return m_str;
}

void KeyboardWidget::slotCloseButtonClicked()
{
    m_tEdit->clear();
    QDialog::reject();
}

void KeyboardWidget::slotSaveButtonClicked()
{
    m_str = m_tEdit->text();
    QDialog::accept();
}

void KeyboardWidget::slotCancelButtonClicked()
{
    m_tEdit->clear();
    QDialog::reject();
}
