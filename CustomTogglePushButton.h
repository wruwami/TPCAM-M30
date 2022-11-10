#ifndef CUSTOMTOGGLEPUSHBUTTON_H
#define CUSTOMTOGGLEPUSHBUTTON_H

#include "CustomPushButton.h"

class CustomTogglePushButton : public CustomPushButton
{
    Q_OBJECT
public:
    explicit CustomTogglePushButton(QWidget *parent = nullptr);
private:
    bool m_bOnOff = false;

signals:

};

#endif // CUSTOMTOGGLEPUSHBUTTON_H
