#include "SearchBoxWidget.h"
#include "ui_SearchBoxWidget.h"

#include "StringLoader.h"

SearchBoxWidget::SearchBoxWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchBoxWidget)
{
    ui->setupUi(this);

    ui->label->setText(LoadString("IDS_SEARCH_TEXT"));
    ui->label->setFontSize(23);

    ui->searchButton->setImage("file_manager", "file_management_search_search_button.bmp");;
}

SearchBoxWidget::~SearchBoxWidget()
{
    delete ui;
}

void SearchBoxWidget::on_firstPlusButton_clicked()
{
    if (ui->checkBox->isChecked())
        firstValue++;
    else
        firstValue += 10;

    if (firstValue > 60)
        firstValue = 60;

    if (firstValue > secondValue)
        firstValue = secondValue;

    ui->firstValueButton->setText(QString::number(firstValue));
    ui->firstValueButton->setFontSize(23);
}

void SearchBoxWidget::on_firstMinusButton_clicked()
{
    if (ui->checkBox->isChecked())
        firstValue--;
    else
        firstValue -= 10;

    if (firstValue < 0)
        firstValue = 0;

    if (firstValue > secondValue)
        firstValue = secondValue;

    ui->firstValueButton->setText(QString::number(firstValue));
    ui->firstValueButton->setFontSize(23);
}

void SearchBoxWidget::on_secondPlusButton_clicked()
{
    if (ui->checkBox->isChecked())
        secondValue++;
    else
        secondValue += 10;

    if (secondValue > 60)
        secondValue = 60;

    if (firstValue > secondValue)
        secondValue = firstValue;

    ui->secondValueButton->setText(QString::number(secondValue));
    ui->secondValueButton->setFontSize(23);
}

void SearchBoxWidget::on_secondMinusButton_clicked()
{
    if (ui->checkBox->isChecked())
        secondValue--;
    else
        secondValue -= 10;

    if (secondValue < 0)
        secondValue = 0;

    if (firstValue > secondValue)
        secondValue = firstValue;

    ui->secondValueButton->setText(QString::number(secondValue));
    ui->secondValueButton->setFontSize(23);
}

void SearchBoxWidget::on_checkBox_clicked()
{
    ui->checkBox_2->setChecked(false);
}

void SearchBoxWidget::on_checkBox_2_clicked()
{
    ui->checkBox->setChecked(false);
}
