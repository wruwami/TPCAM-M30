#include "CustomComboBox.h"

CustomComboBox::CustomComboBox(QWidget *parent) : QComboBox(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
