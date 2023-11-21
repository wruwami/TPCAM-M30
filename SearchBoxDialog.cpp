#include "SearchBoxDialog.h"
#include "ui_SearchBoxDialog.h"

#include <QPainter>
#include <QDesktopWidget>

#include "StringLoader.h"
#include "WidgetSize.h"
#include "FileManager.h"

SearchBoxDialog::SearchBoxDialog(QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchBoxDialog)
{
    ui->setupUi(this);

    this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


    ui->titleLabel->setText(title);
    ui->titleLabel->setFontSize(23);
    ui->searchTextLabel->setText(LoadString("IDS_SEARCH_TEXT"));
    ui->searchTextLabel->setFontSize(23);

    ui->searchButton->setImage("file_manager", "file_management_search_search_button.bmp");
//    ui->closePushButton->setText(LoadString("IDS_BACK"));
    ui->closePushButton->setStyleSheet(QString("QPushButton {image : url(%0images/MessageBox/closeButton.png); border : 2px solid blue;} QPushButton:pressed {border : 2px solid red;}").arg(GeteMMCPath() + "/"));
    ui->closePushButton->setFontSize(23);

    resize(GetWidgetSize(QSize(1208, 702)));

//    setStyleSheet("QWidget. {border: 5px solid black;}");

    connect(ui->closePushButton, &QAbstractButton::clicked, this, &QWidget::close);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

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
    ui->firstValueButton->setFontSize(23);
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
    ui->firstValueButton->setFontSize(23);
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
    ui->secondValueButton->setFontSize(23);
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
    ui->secondValueButton->setFontSize(23);
}

void SearchBoxDialog::on_checkBox_clicked()
{
    ui->checkBox_2->setChecked(false);
}

void SearchBoxDialog::on_checkBox_2_clicked()
{
    ui->checkBox->setChecked(false);
}

void SearchBoxDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(rect().x(), rect().y(), width() - 2, height() - 2);

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

void SearchBoxDialog::on_searchButton_clicked()
{
    accept();
}

