#include "CustomTogglePushButton.h"

CustomTogglePushButton::CustomTogglePushButton(QWidget *parent)
    : CustomPushButton{parent}
{
    connect(this, &QPushButton::clicked, [=]() {
        m_bOnOff = !m_bOnOff;
        if (m_bOnOff)
        {
            //            setStyleSheet(QString("QPushButton {%0 background-color : #25759B; border:none;}").arg(m_stylesheet));
            //            setBackGroundColor(this, 0x25759B);
        }
        else
        {
            //            setStyleSheet(QString("QPushButton {%0 background-color : #52A9C1; border:none;}").arg(m_stylesheet));
            //            setBackGroundColor(this, 0x52A9C1);
        }
    });

}
