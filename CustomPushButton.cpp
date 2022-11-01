#include "CustomPushButton.h"

CustomPushButton::CustomPushButton(QWidget *parent) : QPushButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
