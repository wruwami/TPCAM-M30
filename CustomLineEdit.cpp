#include "CustomLineEdit.h"

#include "FontSize.h"

#include <QLocale>

#include "KeyboardDialog.h"
#include "KeypadDialog.h"
#include "StringLoader.h"
#include "WidgetSize.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    QLocale qLocale;
//    setLocale(qLocale);
}

void CustomLineEdit::SetMode(Mode nMode)
{
    m_nMode = nMode;
}

QString CustomLineEdit::GetString()
{
    return m_strText;
}

QString CustomLineEdit::GetNumber()
{
    return m_strNum;
}

void CustomLineEdit::setFontSize(int font_size)
{
    int calc_font_size = GetFontSize(font_size);
    QFont font = this->font();
    font.setPixelSize(calc_font_size);
    this->setFont(font);
}

void CustomLineEdit::resizeEvent(QResizeEvent *event)
{
//    QFont font;
//    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
//    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
//        font.setPointSizeF(FontSize::Minimum);
//    this->setFont(font); //설정된 폰트를 위젯에 적용
}

void CustomLineEdit::mousePressEvent(QMouseEvent *event)
{
    switch (m_nMode)
    {
    case KeyboardType:
    {
        KeyboardDialog keyboardDialog(this->text(), GetLanguage());
        if (keyboardDialog.exec() == QDialog::Accepted)
        {
            this->setText(keyboardDialog.str());
            m_strText = keyboardDialog.str();
            emit sig_text(keyboardDialog.str());
        }
    }
        break;
    case KeypadType:
    {
        KeypadDialog keypadDialog(this->text());
        if (keypadDialog.exec() == QDialog::Accepted)
        {
            this->setText(keypadDialog.str());
            m_strNum = keypadDialog.str();
            emit sig_num(keypadDialog.str());
        }

    }
        break;

    }

}
