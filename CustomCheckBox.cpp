#include "CustomCheckBox.h"

CustomCheckBox::CustomCheckBox(QWidget *parent) : QCheckBox(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
