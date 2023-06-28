#include "SearchBoxDialog.h"
#include "ui_SearchBoxDialog.h"

#include "StringLoader.h"
#include "WidgetSize.h"

SearchBoxDialog::SearchBoxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchBoxDialog)
{
    ui->setupUi(this);

    this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);



    ui->searchTextLabel->setText(LoadString("IDS_SEARCH_TEXT"));

    ui->searchButton->setImage("file_manager", "file_management_search_search_button.bmp");
    ui->closePushButton->setText(LoadString("IDS_BACK"));

    resize(GetWidgetSize(QSize(1208, 702)));

    connect(ui->closePushButton, &QAbstractButton::clicked, this, &QWidget::close);
}

SearchBoxDialog::~SearchBoxDialog()
{
    delete ui;
}

void SearchBoxDialog::on_firstPlusButton_clicked()
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
}

void SearchBoxDialog::on_firstMinusButton_clicked()
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
}

void SearchBoxDialog::on_secondPlusButton_clicked()
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
}

void SearchBoxDialog::on_secondMinusButton_clicked()
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
}

void SearchBoxDialog::on_checkBox_clicked()
{
    ui->checkBox_2->setChecked(false);
}

void SearchBoxDialog::on_checkBox_2_clicked()
{
    ui->checkBox->setChecked(false);
}

int SearchBoxDialog::getSecondValue() const
{
    return secondValue;
}

void SearchBoxDialog::setSecondValue(int value)
{
    secondValue = value;
}

int SearchBoxDialog::getFirstValue() const
{
    return firstValue;
}

void SearchBoxDialog::setFirstValue(int value)
{
    firstValue = value;
}
