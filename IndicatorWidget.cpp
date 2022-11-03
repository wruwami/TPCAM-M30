#include "IndicatorWidget.h"
#include "ui_IndicatorWidget.h"
#include "CustomPushButton.h"

#include <QFile>

IndicatorWidget::IndicatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorWidget)
{
    QFile file(":/style/indicatorWidget.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    setStyleSheet(styleSheet);

    ui->setupUi(this);
    ui->onPushButton->setVisible(false);
    ui->offPushButton->setVisible(false);
}

IndicatorWidget::~IndicatorWidget()
{
    delete ui;
}

void IndicatorWidget::on_cameraPushButton_clicked()
{
    clearSecondForuthRow();
}

void IndicatorWidget::on_screenRecordingPushButton_clicked()
{
    ui->onPushButton->setVisible(true);
    ui->offPushButton->setVisible(true);
}

void IndicatorWidget::on_daynNightPushButton_clicked()
{
    clearSecondForuthRow();

}

void IndicatorWidget::on_gpsPushButton_clicked()
{
    clearSecondForuthRow();
}

void IndicatorWidget::on_comPushButton_clicked()
{
    clearSecondForuthRow();
}

void IndicatorWidget::on_speedPushButton_clicked()
{
    clearSecondForuthRow();
}

void IndicatorWidget::on_enforcementPushButton_clicked()
{
    clearSecondForuthRow();
}

void IndicatorWidget::on_weatherPushButton_clicked()
{
    clearSecondForuthRow();
    m_pSunnyPushButton = new CustomPushButton();
    m_pRainyPushButton = new CustomPushButton();

//    ui->blankWidget->setAcceptDrops();
    ui->gridLayout->addWidget(m_pSunnyPushButton, 1, 1);
    ui->gridLayout->addWidget(m_pRainyPushButton , 1, 2);
}

void IndicatorWidget::clearSecondForuthRow()
{
    for (int i = 7 ; i < 14 ; i++)
    {
        QLayoutItem* item = ui->gridLayout->takeAt(0);
        if (item != nullptr)
            delete item;
    }

}
