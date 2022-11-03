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
    m_pWifiPushButton = new CustomPushButton();
    m_pBTPushButton = new CustomPushButton();
    m_pEthernetPushButton = new CustomPushButton();

//    ui->gridLayout->setColumnStretch(0, 3);
    ui->gridLayout->addWidget(m_pWifiPushButton, 1, 4);
    ui->gridLayout->addWidget(m_pBTPushButton , 1, 5);
    ui->gridLayout->addWidget(m_pEthernetPushButton , 1, 6);

}

void IndicatorWidget::on_speedPushButton_clicked()
{
    clearSecondForuthRow();
    m_pSTPushButton = new CustomPushButton();
    m_pLTPushButton = new CustomPushButton();

    ui->gridLayout->setColumnStretch(0, 3);
    ui->gridLayout->addWidget(m_pSTPushButton, 1, 3);
    ui->gridLayout->addWidget(m_pLTPushButton , 1, 4);

}

void IndicatorWidget::on_enforcementPushButton_clicked()
{
    clearSecondForuthRow();
    m_pImagePushButton = new CustomPushButton();
    m_pVideoPushButton = new CustomPushButton();
    m_pImageVideoPushButton = new CustomPushButton();

//    ui->gridLayout->setColumnStretch(0, 3);
    ui->horizontalLayout2->addWidget(m_pImagePushButton, 1, 3);
    ui->horizontalLayout2->addWidget(m_pImageVideoPushButton , 1, 4);
    ui->gridLayout->addWidget(m_pVideoPushButton , 1, 5);


}

void IndicatorWidget::on_weatherPushButton_clicked()
{
//    clearSecondForuthRow();
    m_pSunnyPushButton = new CustomPushButton();
    m_pRainyPushButton = new CustomPushButton();

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->insertWidget(1, m_pSunnyPushButton, 2);
    ui->horizontalLayout2->insertWidget(2, m_pRainyPushButton ,2);

    ui->horizontalLayout2->setStretch(6, 1);
}

void IndicatorWidget::clearSecondForuthRow()
{
    for (int i = 0 ; i < 7 ; i++)
    {
        QLayoutItem* item = ui->horizontalLayout2->takeAt(i);
        if (item != nullptr)
        {
            delete item->widget();
            delete item;
        }
    }
}
