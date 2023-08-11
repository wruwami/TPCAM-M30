#include "SdCardMemoryLack.h"
#include "ui_SdCardMemoryLack.h"

SdCardMemoryLack::SdCardMemoryLack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SdCardMemoryLack)
{
    ui->setupUi(this);
}

SdCardMemoryLack::~SdCardMemoryLack()
{
    delete ui;
}
