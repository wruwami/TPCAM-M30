#include "IndicatorWidget.h"
#include "ui_IndicatorWidget.h"
#include "CustomPushButton.h"

#include <QFile>

IndicatorWidget::IndicatorWidget(QWidget *parent) :
    QDialog(parent),
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
    clearSecondRow();
}

void IndicatorWidget::on_screenRecordingPushButton_clicked()
{
    ui->onPushButton->setVisible(true);
    ui->offPushButton->setVisible(true);
}

void IndicatorWidget::on_daynNightPushButton_clicked()
{
    clearSecondRow();
    m_pCameraExposePushButton = new CustomPushButton;
    m_pCameraFocusPushButton = new CustomPushButton;

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(0));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->addWidget(m_pWifiPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pBTPushButton, 2);

}

void IndicatorWidget::on_gpsPushButton_clicked()
{
    clearSecondRow();
    m_pDay1PushButton = new CustomPushButton;
    m_pDay2PushButton = new CustomPushButton;
    m_pDay3PushButton = new CustomPushButton;
    m_pNight1PushButton = new CustomPushButton;
    m_pNight2PushButton = new CustomPushButton;
    m_pNight3PushButton = new CustomPushButton;

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(0));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(5));
    ui->horizontalLayout2->addWidget(m_pDay1PushButton, 2);
    ui->horizontalLayout2->addWidget(m_pDay2PushButton, 2);
    ui->horizontalLayout2->addWidget(m_pDay3PushButton, 2);
    ui->horizontalLayout2->addWidget(m_pNight1PushButton, 2);
    ui->horizontalLayout2->addWidget(m_pNight2PushButton, 2);
    ui->horizontalLayout2->addWidget(m_pNight3PushButton, 2);
}

void IndicatorWidget::on_comPushButton_clicked()
{
    clearSecondRow();
    m_pWifiPushButton = new CustomPushButton();
    m_pBTPushButton = new CustomPushButton();
    m_pEthernetPushButton = new CustomPushButton();

    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(6));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(5));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->addWidget(m_pWifiPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pBTPushButton, 2);
    ui->horizontalLayout2->addWidget(m_pEthernetPushButton, 2);
}

void IndicatorWidget::on_speedPushButton_clicked()
{
    clearSecondRow();
    m_pSTPushButton = new CustomPushButton();
    m_pLTPushButton = new CustomPushButton();

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));
    ui->horizontalLayout2->insertWidget(3, m_pSTPushButton, 2);
    ui->horizontalLayout2->insertWidget(4, m_pLTPushButton , 2);
    ui->horizontalLayout2->setStretch(6, 1);

}

void IndicatorWidget::on_enforcementPushButton_clicked()
{
    clearSecondRow();
    m_pImagePushButton = new CustomPushButton();
    m_pVideoPushButton = new CustomPushButton();
    m_pImageVideoPushButton = new CustomPushButton();

//    ui->gridLayout->setColumnStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(3));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(4));

    ui->horizontalLayout2->insertWidget(2, m_pImagePushButton, 2);
    ui->horizontalLayout2->insertWidget(3, m_pImageVideoPushButton , 2);
    ui->horizontalLayout2->insertWidget(4, m_pVideoPushButton , 2);


}

void IndicatorWidget::on_weatherPushButton_clicked()
{
    clearSecondRow();
    m_pSunnyPushButton = new CustomPushButton();
    m_pRainyPushButton = new CustomPushButton();

    ui->horizontalLayout2->setStretch(0, 3);
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(1));
    ui->horizontalLayout2->removeItem(ui->horizontalLayout2->takeAt(2));
    ui->horizontalLayout2->insertWidget(1, m_pSunnyPushButton, 2);
    ui->horizontalLayout2->insertWidget(2, m_pRainyPushButton ,2);

    ui->horizontalLayout2->setStretch(6, 1);
}

void IndicatorWidget::clearSecondRow()
{
//    for (int i = 0 ; i < 7 ; i++)
//    {
//        QLayoutItem* item = ui->horizontalLayout2->takeAt(i);
//        if (item != nullptr)
//        {
//            delete item->widget();
//            delete item;
//        }
//    }
    QLayoutItem* item;
    while ( ( item = ui->horizontalLayout2->takeAt( 0 ) ) != nullptr )
    {
        delete item->widget();
        delete item;
    }

    for (int i = 0 ; i < 7 ; i++)
    {
        QSpacerItem *item2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->horizontalLayout2->addItem(item2);
        ui->horizontalLayout2->setStretch(i, 2);
    }

}
